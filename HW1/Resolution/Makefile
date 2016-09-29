CC = gcc
TARGET = imgQR
OUTFILES = ./*.bmp

imgQR: imgQR.c
	$(CC) $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OUTFILES)
