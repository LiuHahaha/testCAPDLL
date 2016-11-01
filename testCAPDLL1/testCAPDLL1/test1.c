#include "stdafx.h"


#define FREQUENCY_SNAPSHOT_VERSION		"FREQSNAP1.1"
#define FREQUENCY_SNAPSHOT_COMMENT_LENGTH	32


struct aFrequencySnapshotSegment{
	int    offset;
	int    numPoints;
	double f1;
	double f2;
};

struct aFrequencySnapshotHeader{
	char   version[12];
	int    headerSize;
	int    timeStamp;
	int    alarmNumber;
	int    numSegments;
	char   comment[32];
	int    channel;
};

double h2nd(double d)
{
	double x;
	long *sptr = (long*)&d;
	long *dptr = (long*)&x;

	dptr[0] = htonl(sptr[1]);
	dptr[1] = htonl(sptr[0]);

	return x;
}

float h2nf(float f)
{
	long x;
	long *lptr = (long*)&f;

	x = htonl(*lptr);

	return *((float*)&x);
}

static void swapFrequencySnapshotHeader(struct aFrequencySnapshotHeader *h){
	h->headerSize  = htonl(h->headerSize);
	h->timeStamp   = htonl(h->timeStamp);
	h->alarmNumber = htonl(h->alarmNumber);
	h->numSegments = htonl(h->numSegments);
	h->channel     = htonl(h->channel);
}

static void swapFrequencySnapshotSegments(struct aFrequencySnapshotSegment *s, int numSegments)
{
	int i;
	for(i=0;i<numSegments;i++,s++){
		s->offset    = htonl(s->offset);
		s->numPoints = htonl(s->numPoints);
		s->f1        = h2nd(s->f1);
		s->f2        = h2nd(s->f2);
	}
}

int doCAPDecode(){
	int fd, size, i, j, error;
	struct aFrequencySnapshotHeader h;
	struct aFrequencySnapshotSegment *h_s;
	char time_buffer[256];
	double deltaF;
	float value;

	/*if(argc < 2){
	printf("usage: readFrequencySnapshot filename\n");
	return(-1);
	}*/

	fd = open("../0728001.cap", O_RDONLY| O_BINARY);
	if(fd == -1){
		printf("Couldn't open '%s'.\n");
		return(-1);
	}
	if(read(fd, (char *)&h, sizeof(h)) != sizeof(h)){
		printf("Error reading header\n");
		return(-1);
	}
	swapFrequencySnapshotHeader(&h); //解析头文件信息
	size = sizeof(struct aFrequencySnapshotSegment) * h.numSegments;
	h_s = (struct aFrequencySnapshotSegment *)malloc(size);
	if(read(fd, (char *)h_s, size) != size){
		printf("Error reading data headers\n");
		return(-1);
	}
	swapFrequencySnapshotSegments(h_s, h.numSegments);
	for(i=0;i<h.numSegments;i++){
		deltaF = (h_s[i].f2 - h_s[i].f1)/(h_s[i].numPoints-1);
		for(j=0;j<h_s[i].numPoints;j++){
			if((error = read(fd, (char *)&value, sizeof(float))) != sizeof(float)){
				printf("Error 0x%x reading data value %d %d\n", error, i, j);
				return(-1);
			}
			value = h2nf(value);
			printf("%7.2f\n",value);
		}
	}
	close(fd);

	system("pause");
	return 0;	
} 