rm saida.txt
make clean
make etapa4
./etapa4 teste.lang s.txt
./etapa4 s.txt s2.txt
diff s.txt s2.txt
