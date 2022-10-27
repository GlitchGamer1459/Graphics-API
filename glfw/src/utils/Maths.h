#pragma once

namespace util {

    template<typename _Tp, typename _LH>
    bool range(_Tp n, _LH low, _LH high) 
    {
        return n >= low && n <= high;
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