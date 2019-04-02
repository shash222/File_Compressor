All: fileCompressor.c
	gcc -g -o fileCompressor fileCompressor.c heap.c huffmanBuilder.c frequencyTable.c

clean:
	rm fileCompressor
