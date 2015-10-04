#ifndef TRIP_METER_H_
#define TRIP_METER_H_

#include "Motor.h"

using namespace ev3api;

class TripMeter {
public:
	TripMeter(int init = 0) : mStartingPointDistance(init) {}
	static void setMotor(Motor *right, Motor *left)
	{
		if (right != 0) {
			mRight = right;
		}
		if (left != 0) {
			mLeft = left;
		}
		return;
	}

	const int getTripDistance()	//起点距離mStartingPointDistanceからの走行距離の取得(mm)
	{
		return (currentOdoDistance() - mStartingPointDistance);
	}

	const int startingPointDistance() { return mStartingPointDistance; }
	void setStartingPointDistance(int distance) { mStartingPointDistance = distance; }
	void resetTrip() { setStartingPointDistance(currentOdoDistance()); }	//トリップリセット。コール時点の走行距離を距離計の起点距離にする

private:
	static Motor *mRight;
	static Motor *mLeft;

	int mStartingPointDistance;
	const int currentMotorCount()			//左右モータ・スタート地点からの累積カウント
	{
		return ((mRight->getCount() + mLeft->getCount()) / 2);
	}
	const int currentOdoDistance()			//左右モータ・スタート地点からのトライク累積走行距離(mm)
	{
		const U16 TIRE_CIRCUMFERENCE = 254;	//mm
		return  -(currentMotorCount() * TIRE_CIRCUMFERENCE / 360 / GEAR_RATIO);
	}
};

#endif //DISTANCE_CONDITION_H_
