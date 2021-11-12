CFLAGS = -std=c++11 -Wall -g

huffman:	main.o encoder.o codedTable.o frequencyTable.o huffmanTree.o decoder.o
	g++ main.o encoder.o codedTable.o frequencyTable.o huffmanTree.o decoder.o -o huffman $(CFLAGS)

main.o:	main.cpp
	g++ -c main.cpp $(CFLAGS)

encoder.o:	encoder.cpp
	g++ -c encoder.cpp $(CFLAGS)

codedTable.o:
	g++ -c codedTable.cpp $(CFLAGS)

frequencyTable.o:
	g++ -c frequencyTable.cpp $(CFLAGS)

huffmanTree.o:
	g++ -c huffmanTree.cpp $(CFLAGS)

decoder.o:
	g++ -c decoder.cpp $(CFLAGS)

clean:
	rm *.o huffman