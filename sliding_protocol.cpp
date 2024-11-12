#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
#define WINDOW_SIZE 4
bool sendFrame(int frameNumber) {
	cout<<"Sending Frame" << frameNumber<<endl;
	
	int lossChance = rand()%10;
	if(lossChance<3){
		cout<<"Frame"<<frameNumber<<"lost!"<<endl;
		return false;
	} else {
		cout<<"Frame"<<frameNumber<<"sent successfully!"<<endl;
		return true;
	}
}

bool receiveAck(int frameNumber) {
	int ackChance = rand()%10;
	if(ackChance<7){
		cout<<"Acknowledgment received for Frame "<<frameNumber<<endl;
		return true;
	} else {
		cout<<"Acknowledgment not received for Frame "<<frameNumber<<endl;
		return false;
	}
}

void selectiveRepeat(int totalFrames) {
	int base=0;
	int nextFrame=0;
	srand(time(0));
	
	while(base<totalFrames){
		while(nextFrame<base+WINDOW_SIZE &&nextFrame<totalFrames) {
			if(sendFrame(nextFrame)){
				nextFrame++;
			}
		}
		for(int i=base;i<nextFrame;i++){
			if(receiveAck(i)){
				base++;
			} else{
				cout<<"Retransmitting Frame"<<i<<endl;
				sendFrame(i);
			}
		}
	}
	cout<<"All frames sent and acknowledged!"<<endl;
}
int main(){
	int totalFrames;
	cout<<"Enter total number of frames: ";
	cin>>totalFrames;
	selectiveRepeat(totalFrames);
	return 0;
}
