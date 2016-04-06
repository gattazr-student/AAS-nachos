#ifdef CHANGED
#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include "bitmap.h"

class FrameProvider {
public:
	/* Create the FrameProvider of nbframes */
	FrameProvider (int nbframes);
	/* De-allocate a FrameProvider */
	~FrameProvider ();
	/* Allocate EmptyFrame initialized at 0 */
	int GetEmptyFrame ();
	/* Release the frame identified by num */
	void ReleaseFrame (int num);
	/* Return the number of available frames */
	int NumAvailFrame ();

private:
	BitMap * bitmapFrames;
	int nbFrames;
};

#endif
#endif