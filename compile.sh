gcc -c library.c
echo "library.c compiled"
gcc -c bank.c
echo "bank.c compiled"
gcc library.o bank.o -o a.out
echo "a.out compiled"
rm bank.o 
rm library.o
./a.out
rm a.out