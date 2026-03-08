
//Move data index

struct Transfer2_X 
{
	enum dtName
	{
		EmptyNG_E3		= 1,
		EmptyGood_E4	= 2,
		NgBuffer_E5		= 3,
		
	
		/*GoodStage1		= 6,
		GoodStage2		= 7,
		NgStage1		= 8,
		NgStage2		= 9,*/

		NgStage1	= 6,
		NgStage2		= 7,
		GoodStage1		= 8,
		GoodStage2		= 9,
		
		Unload1_GN_E6	= 4,
		Unload1_E3_E6	= 10,
		Unload1_E5_E6	= 11,

		Unload2_GN_E7	= 5,
		Unload2_E3_E7	= 12,
		Unload2_E5_E7	= 13, 
	};
};


struct Transfer2_Z 
{
	enum dtName
	{
		NgStage1_Up = 11,
		NgStage2_Up = 12,
		GoodStage1_Up = 13,
		GoodStage2_Up = 14, 
	};
};



struct UnloadPicker1_X
{
	enum dtName
	{
		Ready = 0,
		InspectStage1 = 1,
		InspectStage2 = 2,
		InspectStage3 = 3,
		InspectStage4 = 4,

		GoodStage1_1_1	= 5,
		GoodStage1_4_1	 = 9,
		GoodStage1_4_10	 = 10,

		GoodStage2_1_1	= 6,
		GoodStage2_4_1	= 11,
		GoodStage2_4_10	= 12,

		NgStage1_1_1	= 7,
		NgStage1_4_1	= 13, 
		NgStage1_4_10	= 14,

		NgStage2_1_1	= 8,
		NgStage2_4_1	= 15,
		NgStage2_4_10	= 16, 
	};
};


struct UnloadPicker1_Y
{
	enum dtName
	{
		Ready = 0,
		InspectStage1 = 1,
		InspectStage2 = 2,
		InspectStage3 = 3,
		InspectStage4 = 4,
		GoodStage1  = 5,
		GoodStage2  = 6,
		NgStage1	= 7,
		NgStage2	= 8,
	};
};

struct UnloadPicker1_Z
{
	enum dtName
	{
		Ready = 0,
		InspectStage1 = 1,
		InspectStage2  = 2,
		InspectStage3 = 3,
		InspectStage4 = 4,
		GoodStage1	= 5,
		GoodStage2	= 6,
		NgStage1	= 7,
		NgStage2	= 8,
	};
};


struct UnloadPicker1_P
{
	enum dtName
	{

		InspectStage = 0,
		GoodStage	= 1,
		NgStage	= 2,
	};
};

struct UnloadPicker2_X
{
	enum dtName
	{
		Ready				= 0,
		InspectStage1		= 1,
		InspectStage2		= 2,
		InspectStage3		= 3,
		InspectStage4		= 4,

		GoodStage1_1_1		= 5,
		GoodStage1_4_1		= 9,
		GoodStage1_4_10		= 10,

		GoodStage2_1_1	= 6,
		GoodStage2_4_1	= 11,
		GoodStage2_4_10	= 12,

		NgStage1_1_1	= 7,
		NgStage1_4_1	= 13, 
		NgStage1_4_10	= 14,

		NgStage2_1_1	= 8,
		NgStage2_4_1	= 15,
		NgStage2_4_10	= 16, 
	};
};


struct UnloadPicker2_Y
{
	enum dtName
	{
		Ready = 0,
		InspectStage1 = 1,
		InspectStage2 = 2,
		InspectStage3 = 3,
		InspectStage4 = 4,
		GoodStage1  = 5,
		GoodStage2  = 6,
		NgStage1	= 7,
		NgStage2	= 8,
	};
};



struct UnloadPicker2_Z
{
	enum dtName
	{
		Ready = 0,
		InspectStage1 = 1,
		InspectStage2  = 2,
		InspectStage3 = 3,
		InspectStage4 = 4,
		GoodStage1	= 5,
		GoodStage2	= 6,
		NgStage1	= 7,
		NgStage2	= 8,
	};
};


struct UnloadPicker2_P
{
	enum dtName
	{

		InspectStage = 0,
		GoodStage	= 1,
		NgStage	= 2,
	};
};

struct InspectStage1_X
{
	enum dtName
	{
		Align = 0,
		Top1 = 1,
		Top2 = 2,
		Buffer = 4,
		Unload = 3,
	};
};

struct InspectStage2_X
{
	enum dtName
	{
		Align = 0,
		Top1 = 1,
		Top2 = 2,
		Buffer = 4,
		Unload = 3,
	};
};



struct InspectStage3_X
{
	enum dtName
	{
		Align = 0,
		Top1 = 1,
		Top2 = 2,
		Buffer = 4,
		Unload = 3,
	};
};


struct InspectStage4_X
{
	enum dtName
	{
		Align = 0,
		Top1 = 1,
		Top2 = 2,
		Buffer = 4,
		Unload = 3,
	};
};


