CC = gcc
TARGET = imgRWbmp
OUTFILES = output1.bmp output2.bmp

imgRWbmp: imgRWbmp.c
	$(CC) $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OUTFILES)
