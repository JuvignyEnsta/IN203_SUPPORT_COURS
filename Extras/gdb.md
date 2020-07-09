# Chasser les bugs avec gdb

Compiler le programme avec les infos de debug :

```
gcc -g -O0 [sources.cpp] -o a.out
# ou
make DEBUG=y [monprog]   # si le Makefile est prévu pour ça
```

Puis démarrer le débuggeur :
```
gdb a.out
```

## Liste des commandes de base

Une fois dans gdb, le kit de survie :

```
     run
(c)  continue
(n)  next

(p)  print <variable>

(b)  break <fonction>
     break <fichier.cpp>:<ligne>

(bt) backtrace
(f)  frame <N>
     up
     down

(l)  list
     edit
```

Appuyer sur `<enter>` repète la dernière commande.

Pour `edit`, il faut avoir un éditeur un peu sympa. Par exemple : 
```
export EDITOR=gedit
export EDITOR=emacs
```



Plus de commandes sur gdb-refcard.pdf

## gdb et threads

```
thread <N>   # pour switcher sur une autre thread
```



## gdb et MPI 

Le plus simple est d'ouvrir une fenêtre par process MPI :
```
mpirun -np 2 xterm -e gdb a.out
```


## Exemple 1 (segfault)

```
[jd@ldmas707z GDB]$ make DEBUG=y Mandelbrot
mpic++ -std=c++11 -fPIC  -fopenmp -g -O0 -Wall -fbounds-check -pedantic -D_GLIBCXX_DEBUG    Mandelbrot.cpp   -o Mandelbrot
[jd@ldmas707z GDB]$ mpirun -np 2 xterm -e gdb Mandelbrot

(gdb) run
Thread 1 "Mandelbrot" received signal SIGSEGV, Segmentation fault.
__memmove_avx_unaligned_erms () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:448
448     ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S: No such file or directory.
(gdb) bt
#0  __memmove_avx_unaligned_erms () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:448
#1  0x00007ffff5af87c8 in opal_convertor_unpack () from /usr/lib/x86_64-linux-gnu/libopen-pal.so.20
#2  0x00007fffdce4a0cb in mca_pml_ob1_recv_request_progress_rndv () from /usr/lib/x86_64-linux-gnu/openmpi/lib/openmpi/mca_pml_ob1.so
#3  0x00007fffdce42a55 in mca_pml_ob1_recv_frag_callback_rndv () from /usr/lib/x86_64-linux-gnu/openmpi/lib/openmpi/mca_pml_ob1.so
#4  0x00007fffe58f838a in mca_btl_vader_poll_handle_frag () from /usr/lib/x86_64-linux-gnu/openmpi/lib/openmpi/mca_btl_vader.so
#5  0x00007fffe58f866e in ?? () from /usr/lib/x86_64-linux-gnu/openmpi/lib/openmpi/mca_btl_vader.so
#6  0x00007ffff5ae809c in opal_progress () from /usr/lib/x86_64-linux-gnu/libopen-pal.so.20
#7  0x00007ffff7911565 in ompi_request_default_wait () from /usr/lib/x86_64-linux-gnu/libmpi.so.20
#8  0x00007ffff79656f7 in ompi_coll_base_gather_intra_linear_sync () from /usr/lib/x86_64-linux-gnu/libmpi.so.20
#9  0x00007fffdaebd14f in ompi_coll_tuned_gather_intra_dec_fixed () from /usr/lib/x86_64-linux-gnu/openmpi/lib/openmpi/mca_coll_tuned.so
#10 0x00007ffff792eda2 in PMPI_Gather () from /usr/lib/x86_64-linux-gnu/libmpi.so.20
#11 0x0000555555561317 in main (nargs=1, argv=0x7fffffffd198) at Mandelbrot.cpp:149
(gdb) f 11
#11 0x0000555555561317 in main (nargs=1, argv=0x7fffffffd198) at Mandelbrot.cpp:149
149                        MPI_COMM_WORLD);
(gdb) print rank
$1 = 0
(gdb) l
144         auto imgloc = computeMandelbrotSet( W, Hloc, maxIter );
145         std::vector<int> imgglob(W*H);
146         MPI_Gather(imgloc.data(), imgloc.size(), MPI_INT,   // emetteurs
147                    imgglob.data(), imgglob.size(), MPI_INT, // receveur
148                    0,                                       // root process
149                    MPI_COMM_WORLD);
150         savePicture("mandelbrot2.tga", W, H, iters, maxIter);
151         MPI_Finalize();
152         return EXIT_SUCCESS;
153      }

# je comprends que le pb est dans MPI_Gather du process 0, je n'ai plus qu'une ligne a suspecter.
```



