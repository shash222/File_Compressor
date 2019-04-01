third: third.c
	gcc -Wall -Werror -fsanitize=address -o fileCompressor fileCompressor.c heap.c huffmanBuilder.c frequencyTable.c

clean:
	rm -rf third
