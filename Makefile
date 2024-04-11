.POSIX:
shyard: stack.o shyard.c shyard.h
	$(CC) $(CFLAGS) shyard.c *.o -o shyard
stack.o: stack.c stack.h
clean:
	rm stack.o shyard
