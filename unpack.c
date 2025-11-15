#include <stdio.h>
#include <stdlib.h>
	
int main(int argc, char *argv[]) {
	
	FILE *fp = fopen(argv[1], "rb");
	
	fseek(fp, 0x10, SEEK_SET);
	
	char filename[50];
	unsigned int offset, size;
	
	while (fscanf(fp, "%s %u %u", filename, &offset, &size) == 3) {
	printf("Output: %s (Offset: %u, Size: %u)\n", filename, offset, size);
	
	long currentpos = ftell(fp);
	
	FILE *out = fopen(filename, "wb");
	
	fseek(fp, offset + 4096, SEEK_SET);
	
	unsigned char *buffer = malloc(size);
	size_t read = fread(buffer, 1, size, fp);
	fwrite(buffer, 1, size, out);
	
	free(buffer);
	fclose(out);
	
	fseek(fp, currentpos, SEEK_SET);
	}
	
	fclose(fp);
	
	return 0;
}
