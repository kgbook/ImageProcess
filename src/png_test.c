#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "png.h"
#include "png_test.h"

KG_U32 png_get_data(PNG_S_DIM *pstDim, KG_CHAR **ppData, KG_CHAR *pszPath)
{
	KG_BOOL bIsPng;
	KG_U8 acHeader[PNG_HEADER_LEN];
	FILE *fpIn;
	png_structp read_ptr;
	png_infop read_info_ptr, end_info_ptr;
	png_bytepp row_ptr;
	KG_U32	u32Width, u32Height, u32Len;
	KG_U32 u32Row, u32Col;
	KG_U32 u32Pos = 0;
	KG_U8 u8ColorType, u8BytePerPixel;
	KG_CHAR *pData;

	if ((KG_NULL == pstDim) || (1 > strlen(pszPath)))
	{
		print_err("error param.\n");
		return KG_FAILURE;
	}

	print_debug("pszPath:%s", pszPath);

	if(KG_NULL == (fpIn = fopen(pszPath, "rb" )) )
	{
		print_err("failed when fopen().");
		return KG_FAILURE;
	}

	memset(acHeader, 0, sizeof(acHeader));
	fread(acHeader, 1, PNG_HEADER_LEN, fpIn);
	bIsPng = !png_sig_cmp(acHeader, 0, PNG_HEADER_LEN);

	if (!bIsPng)
	{
		print_err("only png file supported!");
		return KG_FAILURE;
	}

	if (KG_NULL == (read_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)))
	{
		print_err("failed when png_create_read_struct().");
		return KG_FAILURE;
	}

	if (KG_NULL == (read_info_ptr = png_create_info_struct(read_ptr)))
	{
		print_err("failed when png_create_info_struct().");
		png_destroy_read_struct(&read_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return KG_FAILURE;
	}

	if (setjmp(png_jmpbuf(read_ptr)))
    {
       png_destroy_read_struct(&read_ptr, &read_info_ptr, &end_info_ptr);
       fclose(fpIn);
       return KG_FAILURE;
    }

	png_init_io(read_ptr, fpIn);
	png_set_sig_bytes(read_ptr, PNG_HEADER_LEN);
	png_read_png(read_ptr, read_info_ptr, PNG_TRANSFORM_EXPAND, NULL);//RGBA8888 or RGB888
	row_ptr = png_get_rows(read_ptr, read_info_ptr);

	u32Width = png_get_image_width(read_ptr, read_info_ptr);
	u32Height = png_get_image_height(read_ptr, read_info_ptr);
	u8ColorType = png_get_color_type(read_ptr, read_info_ptr);
	u8BytePerPixel = (PNG_COLOR_TYPE_RGBA == u8ColorType) ? 4 : 3;	//RGBA or RGB
	u32Len = u32Width * u32Height * u8BytePerPixel;

	print_debug("u32Width:%u, u32Height:%u, u32Len:%u", u32Width, u32Height, u32Len);

	if (NULL == (pData = (KG_CHAR *)malloc(u32Len)))
	{
		print_err("failed when malloc().");
		return KG_FAILURE;
	}

	for (u32Row = 0; u32Row < u32Height; u32Row++)
	{
		for (u32Col = 0; u32Col < u32Width * u8BytePerPixel; u32Col += u8BytePerPixel)
		{
			pData[u32Pos++] = row_ptr[u32Row][u32Col];			//red
			pData[u32Pos++] = row_ptr[u32Row][u32Col + 1];		//green
			pData[u32Pos++] = row_ptr[u32Row][u32Col + 2];		//blue
			pData[u32Pos++] = row_ptr[u32Row][u32Col + 3];		//alpha
		}
	}

	png_destroy_read_struct(&read_ptr, &read_info_ptr, (png_infopp)NULL);

	pstDim->u32Width = u32Width;
	pstDim->u32Height = u32Height;
	pstDim->u32Len = u32Len;
	*ppData = pData;

	return KG_SUCCESS;
}

#if 1
KG_S32 main(KG_S32 argc, KG_CHAR **argv)
{
	KG_U32 u32Index;
	KG_CHAR *acFilename, *auImgData;
	PNG_S_DIM stDim;
	FILE *fpHeader, *fpBin, *fpRgb;

	if ((argc < 2) || (1 > strlen(argv[1])))
	{
		print_err("error param.\n");
		return KG_FAILURE;
	}

	if ((KG_NULL == (fpHeader = fopen("header.txt", "w")))
			|| (KG_NULL == (fpBin = fopen("bin.txt", "w")))
			|| (KG_NULL == (fpRgb = fopen("png.rgb8888", "w"))))
	{
		print_err("failed when fopen().");
		return KG_FAILURE;
	}

	acFilename = argv[1];	
	memset(&stDim, 0, sizeof(stDim));
	
	if (KG_SUCCESS != png_get_data(&stDim, &auImgData, acFilename))
	{
		print_err("failed when png_get_data!");
		return KG_FAILURE;
	}

	for (u32Index = 0; u32Index < stDim.u32Len; u32Index++)
	{
		fprintf(fpBin, "%3u, ", auImgData[u32Index]);

		if (0 == ((u32Index + 1) % 0x10))
		{
			fprintf(fpBin, "\n");
		}
	}

	fprintf(fpHeader, "width = %u\n", stDim.u32Width);
	fprintf(fpHeader, "height = %u\n", stDim.u32Height);
	fprintf(fpHeader, "len = %u\n", stDim.u32Len);

	fwrite(auImgData, 1, stDim.u32Len, fpRgb);

	if (NULL != fpBin)
	{
		fclose(fpBin);
		fpBin = NULL;
	}

	if (NULL != fpHeader)
	{
		fclose(fpHeader);
		fpHeader = NULL;
	}

	if (NULL != fpRgb)
	{
		fclose(fpRgb);
		fpRgb = NULL;
	}
	
	return KG_SUCCESS;
}
#endif
