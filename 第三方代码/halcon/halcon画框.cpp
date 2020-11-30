#include "pch.h"

#include "halcon»­¿ò.h"

void gen_CROSS(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column, HTuple hv_LineLenght) {
	// Local iconic variables
	HObject  ho_RegionLines1, ho_RegionLines2;

	GenRegionLine(&ho_RegionLines1, hv_Row - (hv_LineLenght / 2), hv_Column, hv_Row + (hv_LineLenght / 2),
		hv_Column);
	GenRegionLine(&ho_RegionLines2, hv_Row, hv_Column - (hv_LineLenght / 2), hv_Row, hv_Column + (hv_LineLenght / 2));
	Union2(ho_RegionLines1, ho_RegionLines2, &(*ho_RegionResult));
	return;
}

void gen_RECTANGLE(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column, HTuple hv_Distance,
	HTuple hv_LineLenght) {
	// Local iconic variables
	HObject  ho_RegionResult1, ho_RegionResult2, ho_RegionResult3;
	HObject  ho_RegionResult4, ho_RegionUnion1, ho_RegionUnion2;

	gen_region_RLineLeftTop(&ho_RegionResult1, hv_Row, hv_Column, hv_Distance, hv_LineLenght);

	gen_region_RLineRightTop(&ho_RegionResult2, hv_Row, hv_Column, hv_Distance, hv_LineLenght);

	gen_region_RLineLeftButton(&ho_RegionResult3, hv_Row, hv_Column, hv_Distance, hv_LineLenght);

	gen_region_RLineRightButton(&ho_RegionResult4, hv_Row, hv_Column, hv_Distance,
		hv_LineLenght);
	Union2(ho_RegionResult1, ho_RegionResult2, &ho_RegionUnion1);
	Union2(ho_RegionResult3, ho_RegionResult4, &ho_RegionUnion2);
	Union2(ho_RegionUnion1, ho_RegionUnion2, &(*ho_RegionResult));
	return;
}

void gen_region_RLineLeftButton(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
	HTuple hv_Distance, HTuple hv_LineLenght) {
	// Local iconic variables
	HObject  ho_RegionLines1, ho_RegionLines2;

	GenRegionLine(&ho_RegionLines1, hv_Row + hv_Distance, hv_Column - hv_Distance, hv_Row + hv_LineLenght,
		hv_Column - hv_Distance);
	GenRegionLine(&ho_RegionLines2, hv_Row + hv_Distance, hv_Column - hv_Distance, hv_Row + hv_Distance,
		hv_Column - hv_LineLenght);
	Union2(ho_RegionLines1, ho_RegionLines2, &(*ho_RegionResult));
	return;
}

void gen_region_RLineLeftTop(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
	HTuple hv_Distance, HTuple hv_LineLenght) {
	// Local iconic variables
	HObject  ho_RegionLines1, ho_RegionLines2;

	GenRegionLine(&ho_RegionLines1, hv_Row - hv_Distance, hv_Column - hv_Distance, hv_Row - hv_LineLenght,
		hv_Column - hv_Distance);
	GenRegionLine(&ho_RegionLines2, hv_Row - hv_Distance, hv_Column - hv_Distance, hv_Row - hv_Distance,
		hv_Column - hv_LineLenght);
	Union2(ho_RegionLines1, ho_RegionLines2, &(*ho_RegionResult));
	return;
}

void gen_region_RLineRightButton(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
	HTuple hv_Distance, HTuple hv_LineLenght) {
	// Local iconic variables
	HObject  ho_RegionLines1, ho_RegionLines2;

	GenRegionLine(&ho_RegionLines1, hv_Row + hv_Distance, hv_Column + hv_Distance, hv_Row + hv_LineLenght,
		hv_Column + hv_Distance);
	GenRegionLine(&ho_RegionLines2, hv_Row + hv_Distance, hv_Column + hv_Distance, hv_Row + hv_Distance,
		hv_Column + hv_LineLenght);
	Union2(ho_RegionLines1, ho_RegionLines2, &(*ho_RegionResult));
	return;
}

void gen_region_RLineRightTop(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
	HTuple hv_Distance, HTuple hv_LineLenght) {
	// Local iconic variables
	HObject  ho_RegionLines1, ho_RegionLines2;

	GenRegionLine(&ho_RegionLines1, hv_Row - hv_Distance, hv_Column + hv_Distance, hv_Row - hv_LineLenght,
		hv_Column + hv_Distance);
	GenRegionLine(&ho_RegionLines2, hv_Row - hv_Distance, hv_Column + hv_Distance, hv_Row - hv_Distance,
		hv_Column + hv_LineLenght);
	Union2(ho_RegionLines1, ho_RegionLines2, &(*ho_RegionResult));
	return;
}