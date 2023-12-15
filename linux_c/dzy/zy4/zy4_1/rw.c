#include <stdio.h>

int main() {
	char filename[] = "moweida.txt";
	FILE *fp;
	char ch;

	// 打开文件并检查是否成功打开
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("无法打开文件。\n");
		return 1;
	}

	// 打开/etc/passwd文件并将其内容写入文件
	FILE *passwd_fp = fopen("/etc/passwd", "r");
	while ((ch = fgetc(passwd_fp)) != EOF) {
		fputc(ch, fp);
	}

	fclose(passwd_fp);
	fclose(fp);

	printf("已成功将/etc/passwd文件的内容写入%s文件。\n", filename);
	return 0;
}




