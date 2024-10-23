#include "filesave.h"
void make_record(char* record, int value)
{
	FILE* rec = fopen("records\\rec_file.txt", "a+");
	if (rec != NULL)fprintf(rec, "%s %d\n", record, value);
	else printf("SAVE FAILURE");
}