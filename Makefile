All: fileCompressor.c
	gcc -o fileCompressor fileCompressor.c heap.c huffmanBuilder.c frequencyTable.c

clean:
	rm -rf fileCompressor
