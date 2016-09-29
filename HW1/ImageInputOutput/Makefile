CC = gcc
TARGET = imgRWbmp
OUTFILES = ./*bmp

imgRWbmp: imgRWbmp.c
	$(CC) $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OUTFILES)
