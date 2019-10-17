#pragma once

class SensorBorder {
public:
	void set();
	int get(int i, int j) { return sensor[i][j]; }
private:
	int sensor[9][9];
};
