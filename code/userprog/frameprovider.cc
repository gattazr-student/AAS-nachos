#ifdef CHANGED
#include "copyright.h"
#include "bitmap.h"
#include "frameprovider.h"

FrameProvider::FrameProvider(int nbframes){
	bitmapFrames = new BitMap(nbframes);
	this->nbFrames = nbframes;
}
FrameProvider::~FrameProvider(){
	delete bitmapFrames;
}

int FrameProvider::GetEmptyFrame (){
	return bitmapFrames->Alea();
}

void FrameProvider::ReleaseFrame (int num){
	bitmapFrames->Clear(num);
}
int FrameProvider::NumAvailFrame (){
	return bitmapFrames->NumMarked();
}

#endif