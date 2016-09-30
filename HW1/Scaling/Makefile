CC = gcc
TARGET = imgScaling
OUTFILES = ./*.bmp

imgScaling: imgScaling.c
	$(CC) $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OUTFILES)
