All:
	@echo "Compilando Tabela Hash..."
	@g++ -Wall -std=c++11 src/main.cpp -I include/ -o bin/tabela
clean:
	@echo "Limpando..."
	@rm bin/*
