#include <stdio.h>

void leakyBucket(int incomingPackets[], int n, int bucketSize, int outflowRate) {
    int bucketContent = 0;
    int i;
    
    for (i = 0; i < n; i++) {
        printf("Incoming packets at time %d: %d\n", i + 1, incomingPackets[i]);
        
        if (incomingPackets[i] + bucketContent <= bucketSize) {
            bucketContent += incomingPackets[i];
        } else {
            printf("Bucket Overflow! Discarding %d packets.\n", incomingPackets[i] - (bucketSize - bucketContent));
            bucketContent = bucketSize;
        }

        printf("Packets sent: %d\n", outflowRate < bucketContent ? outflowRate : bucketContent);
        bucketContent -= outflowRate;
        
        if (bucketContent < 0) {
            bucketContent = 0;
        }

        printf("Current bucket content: %d\n\n", bucketContent);
    }
}

int main() {
    int bucketSize, outflowRate, n, i;

    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);
    printf("Enter outflow rate: ");
    scanf("%d", &outflowRate);
    printf("\nEnter the number of incoming packets: ");
    scanf("%d", &n);

    int incomingPackets[n];
    for (i = 0; i < n; i++) {
        printf("Enter the number of packets arriving at time %d: ", i + 1);
        scanf("%d", &incomingPackets[i]);
    }

    printf("\nLeaky Bucket Algorithm Simulation:\n\n");
    leakyBucket(incomingPackets, n, bucketSize, outflowRate);

    return 0;
}
