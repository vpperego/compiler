rm saida.txt
make clean
make etapa3
./etapa3 teste.lang s.txt
./etapa3 s.txt s2.txt
diff s.txt s2.txt
