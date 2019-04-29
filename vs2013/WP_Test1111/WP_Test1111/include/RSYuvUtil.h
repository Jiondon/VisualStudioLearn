#ifndef RS_YUV_UTIL_H_
#define RS_YUV_UTIL_H_

typedef unsigned int UINT32;
typedef unsigned char UINT8;

#ifdef RSYUVUTIL_EXPORTS
#define RSYUVUTIL_API __declspec(dllexport)
#else
#define RSYUVUTIL_API __declspec(dllimport)
#endif

#ifndef __cplusplus
extern "C"{
#endif
	enum
	{
		NO_SUCH_FORMAT = 1,
		CAN_NOT_CONVERT = 2,
		CAN_NOT_SCALE = 3,
		CAN_NOT_ROTATE = 4,
		CAN_NOT_MIRROR,
		CAN_NOT_GRAY,
		CAN_NOT_CROP,
	};

	enum
	{
		NONE = 0,
		IMAGE_FORMAT_YUV420P,
		IMAGE_FORMAT_YUV420SP,
		IMAGE_FORMAT_YUV422P,
		IMAGE_FORMAT_YUV444P,
		IMAGE_FORMAT_ARGB,
		IMAGE_FORMAT_RGB24,
		IMAGE_FORMAT_BGR24,
	};

	/*********************************************************************************************************
	Function: Roseek_YuvUtil_YuvImageConvert.
	Description: Convert the format of the image.
	Input: "pSrcImage" is the pointer array of source image, as usual ,pDestImage[0] for y component head address of 
		  source image, pDestImage[1] for head address of u component or head address of uv component,
		  pDestImage[2] for head address of v component, but only pSrcImage[0] should be use when converting RGB image;
		"SrcFormat" is the format of source image; 
		"DestFormat" is the format of source image convert to;
		"Width" / "Height" is size of pSrcImage.
	Output: "pDestImage" is the pointer array of target image, pDestImage[0] for y component head address of 
		  source image, pDestImage[1] for head address of u component or head address of uv component,
		  pDestImage[2] for head address of v component, and only pDestImage[0] will be written when convert RGB image.
	Return: Return 0 for successful, other values for failure.
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_YuvImageConvert(const UINT8 *pSrcImage[4], UINT32 SrcFormat,
				  UINT8 *pDestImage[4], UINT32 DestFormat, UINT32 Width, UINT32 Height);

	/**********************************************************************************************************
	Function: Roseek_YuvUtil_YuvImageScale.
	Description: Scale image.
	Input: "pSrcImage" is the pointer array of source image, as usual ,pSrcImage[0] for y component head address of 
		  source image, pSrcImage[1] for head address of u compoent, pSrcImage[2] for head address of v compoent, 
		  but only pSrcImage[0] should be used when scaling ARGB image;
		"Format" is the format of source image , it can only be IMAGE_FORMAT_ARGB or IMAGE_FORMAT_YUV420P;
		"SrcWidth" / "SrcHeight" is size of pSrcImage;
		"DestWidth" / "DestHeight" is size of pSrcImage scale to;
		"FilterMode" is the filter mode of scaling.
	Output: "pDestImage" is the pointer array of source image, pDestImage[0] for y component head address of 
		  source image, pDestImage[1] for head address of u, pDestImage[2] for head address of v compoent, and only 
		  pDestImage[0] will be written when scaling ARGB image.
	Return: Return 0 for successful, other values for failure.
	Others: If "FilterMode" is 0, a simple nearest-neighbor algorithm is used, This produces basic (blocky) quality at the 
		  fastest speed; If "FilterMode" is 2, interpolation is used to produce a better quality image, at the expense of speed.
		  If "FilterMode" is 3, averaging is used to produce ever better quality image, at further expense of speed;
		You should pay more attention to the buffer size of target image when scaling a image because the difference between
		  two images.
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_YuvImageScale(const UINT8 *pSrcImage[4], UINT32 Format,
				  UINT32 SrcWidth, UINT32 SrcHeight, UINT8 *pDestImage[4], UINT32 DestWidth,
				  UINT32 DestHeight, UINT32 FilterMode);

	/**********************************************************************************************************
	Function: Roseek_YuvUtil_YuvImageRotate.
	Description: Rotate the source image.
	Input: "pSrcImage" is the pointer array of source image, pSrcImage[0] for y component head address of source image,
		  pSrcImage[1] for head address of u compoent or head address of uv compoent,  pSrcImage[2] for head address 
		  of v compoent,but only pSrcImage[0] should be use when convert ARGB image;
		"Format" is the format of image;
		"Width" / "Height" is size of pSrcImage;
		"RotationMode" is angle of pDestImage rotate.
	Output: "pDestImage" is the pointer array of target image, pDestImage[0] for y component head address of 
		  source image, pDestImage[1] for head address of u component or head address of uv component,
		  pDestImage[2] for head address of v component, and only pDestImage[0] will be written when convert ARGB image.
	Return: Return 0 for successful, other values for failure.
	Others: "RotationMode" can only be 0, 90, 180 or 270;
		"Format" can only be ImageRotate_YUV420P, IMAGE_FORMAT_ARGB or IMAGE_FORMAT_YUV420SP;
		when rotating YUV420SP format, this function will output a YUV420P image.
		You should pay attention to the width and height of image after rotation. 
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_YuvImageRotate(const UINT8 *pSrcImage[4], UINT32 Format,
				  UINT32 Width, UINT32 Height, UINT8 *pDestImage[4], UINT32 RotationMode);

	/**********************************************************************************************************
	Function: Roseek_YuvUtil_YuvImageMirror;
	Decription: Mirror conversion;
	Input: "pSrcImage" is the pointer array of source image, pSrcImage[0] for y component head address of source image, 
		  pSrcImage[1] for head address of u compoent , pSrcImage[2] for head address of v compoent, but only pSrcImage[0]
		  should be used when convert ARGB format;
		"Format": is the format of image;
		"Width" / "Height" is size of pSrcImage;
	Output:  "pDestImage" is the pointer array of source image, pDestImage[0] for y component head address of source image, 
		  pDestImage[1] for head address of u compoent, pDestImage[2] for head address of v compoent, but only pDestImage[0]
		  should be used when convert ARGB format;
	Return: Return 0 for successful, other values for failure.
	others: Format can only be IMAGE_FORMAT_YUV420P or IMAGE_FORMAT_ARGB.
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_YuvImageMirror(const UINT8 *pSrcImage[4],
				  UINT32 Format, UINT32 Width, UINT32 Height, UINT8 *pDestImage[4]);
	
	/**********************************************************************************************************
	Function: Roseek_YuvUtil_YuvImageGray.
	Description: Convert image to gray image.
	Input: "pSrcImage" is the pointer array of source image, only pSrcImage[0] should be used, pSrcOmage[0] is the head 
		  address of source image. 
		"Format": is the format of image;
		"Width" / "Height" is size of pSrcImage;
	Output: "pDestImage" is the pointer array of target buffer, only pSrcImage[0] should be used, pSrcOmage[0] is the head 
		  address of source image. 
	Return: Return 0 for successful, other values for failure.
	Others: "Format" can only be IMAGE_FORMAT_ARGB.
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_YuvImageGray(const UINT8 *pSrcImage[4],
				  UINT32 Format, UINT32 Width, UINT32 Height, UINT8 *pDestImage[4]);

	/**********************************************************************************************************
	Function: Roseek_YuvUtil_CropToYUV420P.
	Description: Convert image to YUV420P with croping ,rotation.
	Input: "pSrcImage" is the pointer address of image, pSrcImage[0] is the head address of source image;
		"Format" is the format of image;
		"CropX" and "CropY" are starting position for cropping;
		"CropWidth" / "CropHeight" is the size to crop the src to;
		"SrcWidth" / "SrcHeight" is size of pSrcImage;
		"RotationMode" is angle of pDestImage rotate.
	Output: "pDestImage" is the pointer array of target image, pDestImage[0] for y component head address of 
		  source image, pDestImage[1] for head address of u component or head address of uv component,
		pDestImage[2] for head address of v component;		
	Return: Return 0 for successful, other values for failure.
	Others: "RotationMode" can only be 0, 90, 180 or 270;
		Format can not be IMAGE_FORMAT_RGB24;
		The value of CropX, CropY, CropWidth and CropHeight should be within reasonable limits;
		The output format is always YUV420P;
		Function can only crop Address continuous image.
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_CropToYUV420P(const UINT8 *pSrcImage, UINT32 Format,
				  UINT8 *pDestImage[4], UINT32 CropX, UINT32 CropY, UINT32 CropWidth,
				  UINT32 CropHeight, UINT32 SrcWidth, UINT32 SrcHeight, UINT32 RotationMode);

	/**********************************************************************************************************
	Function: Roseek_YuvUtil_CropToARGB.
	Description: Convert image to ARGB with croping ,rotation.
	Input: "pSrcImage" is the pointer address of imagep, pSrcImage[0] is the head address of source image;
		"Format" is the format of image;
		"CropX" and "CropY" are starting position for cropping;
		"CropWidth" / "CropHeight" is the size to crop the src to;
		"SrcWidth" / "SrcHeight" is size of pSrcImage;
		"RotationMode" is angle of pDestImage rotate, it can only be 0.
	Output: "pDestImage" is the pointer array of target image, and only pDestImage[0] will be writen image data;
	Return: Return 0 for successful, other values for failure.
	Others: Format can not be IMAGE_FORMAT_RGB24;
		The value of CropX, CropY, CropWidth and CropHeight should be within reasonable limits;
		The output format is always ARGB;
		"RotationMode" can only be 0;
		Function can only crop Address continuous image.
	**********************************************************************************************************/
	RSYUVUTIL_API int Roseek_YuvUtil_CropToARGB(const UINT8 *pSrcImage, UINT32 Format,
				  UINT8 *pDestImage, UINT32 CropX, UINT32 CropY, UINT32 CropWidth,
				  UINT32 CropHeight, UINT32 SrcWidth, UINT32 SrcHeight, UINT32 RotationMode);

#ifndef __cplusplus
};
#endif
#endif