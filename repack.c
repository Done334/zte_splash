#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	FILE *out = fopen("logo_new.bin", "wb");
	
	char header[4096] = {0};
	fwrite(header, 1, 4096, out);
	
	char metadata[4096] = {0};
	int metapos = 0;
	unsigned int currentOffset = 0;
	
	for(int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "rb");
		if (fp == NULL) continue;
		
		fseek(fp, 0, SEEK_END);
		unsigned int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		
		metapos += sprintf(metadata + metapos, " %s %u %u", argv[i], currentOffset, size);
		
		char *buffer = malloc(size);
		fread(buffer, 1, size, fp);
		fwrite(buffer, 1, size, out);
		fclose(fp);
		free(buffer);
		
		currentOffset += size;
	}
	
	if (metapos > 0 && metapos < sizeof(metadata) - 1) {
		metadata[metapos] = ' ';
		metapos++;
	}
	
	fseek(out, 0x10, SEEK_SET);
	fwrite(metadata, 1, metapos, out);
	fclose(out);
	
	printf("Complete\nOutput: logo_new.bin\n");
	
	return 0;
}
