#include <utility>

typedef std::pair<int, int> xyLoc;
enum FishTypeEnum
{
  Unknown,
  Flounder,
  Skate,
  Cod,
  Haddock
};

class Fish
{
private:
	FishTypeEnum fishType;
	int subType;
	int frameCounted;
	xyLoc fishLoc;

public:
	Fish(FishTypeEnum fType, int frame);
	void setFishType(FishTypeEnum type);
	void setFishSubType(int sType);
	void setXYLoc(int row, int col);
	FishTypeEnum getFishType();
	int getFishSubType();
	int getFrameCounted();
	xyLoc getXYLoc();
};