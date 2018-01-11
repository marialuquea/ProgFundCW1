all:
	gcc -o spell spell.c
	./spell

sentences_test:
	gcc -o spell spell.c
	./spell -i sentences_test.txt -o output.txt

sentences_test_no_case:
	gcc -o spell spell.c
	./spell -i sentences_test.txt -o output.txt -c

single_words_test:
	gcc -o spell spell.c
	./spell -i single_words_test.txt -o output.txt

single_words_test_no_case:
	gcc -o spell spell.c
	./spell -i single_words_test.txt -o output.txt -c

clean:
	rm *.o
	rm spell