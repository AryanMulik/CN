#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int base = 0;
int nextSeqNum = 0;
int timer = 0;
const int TIMEOUT = 3;

void sendFrame(int frame) {
    cout << "Sending frame " << frame << endl;
    if (rand() % 10 < 2) {
        cout << "Frame " << frame << " lost!" << endl;
    }
}

bool isAckReceived(int& ack, int totalFrames) {
    if (timer >= TIMEOUT) {
        ack = base + rand() % (nextSeqNum - base);
        cout << "Received ACK for frame " << ack << endl;
        base = ack + 1;
        timer = 0;
        return true;
    }
    return false;
}

void sendWindow(int totalFrames, int windowSize) {
    int ack;
    while (base < totalFrames) {
        while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames) {
            sendFrame(nextSeqNum);
            nextSeqNum++;
        }

        for (timer = 0; timer <= TIMEOUT; ++timer) {
            if (isAckReceived(ack, totalFrames)) break;
        }

        if (timer >= TIMEOUT) {
            cout << "Timeout! Resending frames starting from " << base << endl;
            nextSeqNum = base;
        }
    }

    cout << "All frames sent successfully!" << endl;
}

int main() {
    srand(time(0));

    int totalFrames, windowSize;

    cout << "Enter total number of frames: ";
    cin >> totalFrames;

    cout << "Enter the window size: ";
    cin >> windowSize;

    sendWindow(totalFrames, windowSize);

    return 0;
}
