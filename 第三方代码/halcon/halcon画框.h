#pragma once

#include <HalconCpp.h>
using namespace  HalconCpp;
void gen_CROSS(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column, HTuple hv_LineLenght);
void gen_RECTANGLE(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column, HTuple hv_Distance,
    HTuple hv_LineLenght);
void gen_region_RLineLeftButton(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
    HTuple hv_Distance, HTuple hv_LineLenght);
void gen_region_RLineLeftTop(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
    HTuple hv_Distance, HTuple hv_LineLenght);
void gen_region_RLineRightButton(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
    HTuple hv_Distance, HTuple hv_LineLenght);
void gen_region_RLineRightTop(HObject* ho_RegionResult, HTuple hv_Row, HTuple hv_Column,
    HTuple hv_Distance, HTuple hv_LineLenght);

