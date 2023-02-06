#pragma once

namespace util {

    template<typename _Tp, typename _LH>
    bool in_range(_Tp n, _LH low, _LH high) 
    {
        return n >= low && n <= high;
    }

	template<typename _Tp, typename _LH>
	float clampf(_Tp in, _LH low, _LH high)
	{
		if (in < low)
			return low;
		else if (in > high)
			return high;
		
		return in;
	}

	template<typename _Tp, typename _LH>
	double clampd(_Tp in, _LH low, _LH high)
	{
		if (in < low)
			return low;
		else if (in > high)
			return high;

		return in;
	}

	template<typename _Tp>
	float rootf(_Tp l)
	{
		const float INIT = l;
		float r = 1;

		while (1) 
		{
			l = (r + l) / 2;
			r = INIT / l;

			if ((int)(l * 10000) == (int)(r * 10000))
				break;
		}

		return l;
	}

	template<typename _Tp>
	double rootd(_Tp l)
	{
		const double INIT = l;
		double r = 1;

		while (1)
		{
			l = (r + l) / 2;
			r = INIT / l;

			if ((int)(l * 10000) == (int)(r * 10000))
				break;
		}

		return l;
	}

	bool isEven(int n)
	{
		return n & 1;
	}

}