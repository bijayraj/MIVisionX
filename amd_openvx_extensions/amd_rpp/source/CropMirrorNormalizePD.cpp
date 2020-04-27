#include <kernels_rpp.h>
#include <vx_ext_rpp.h>
#include <stdio.h>
#include <iostream>
#include "internal_rpp.h"
#include "internal_publishKernels.h"
#include </opt/rocm/rpp/include/rpp.h>
#include </opt/rocm/rpp/include/rppdefs.h>
#include </opt/rocm/rpp/include/rppi.h>


struct CropMirrorNormalizebatchPDLocalData { 
	RPPCommonHandle handle;
	rppHandle_t rppHandle;
	Rpp32u device_type; 
	Rpp32u nbatchSize; 
	RppiSize *srcDimensions;
	RppiSize maxSrcDimensions;
	RppiSize *dstDimensions;
	RppiSize maxDstDimensions;
	RppPtr_t pSrc;
	RppPtr_t pDst;
	vx_uint32 *start_x;
	vx_uint32 *start_y;
	vx_float32  *mean;
    vx_float32 *std_dev;
    vx_uint32 *mirror;
    vx_uint32 chnShift; //NHWC to NCHW
#if ENABLE_OPENCL
	cl_mem cl_pSrc;
	cl_mem cl_pDst;
#endif 
};

static vx_status VX_CALLBACK refreshCropMirrorNormalizebatchPD(vx_node node, const vx_reference *parameters, vx_uint32 num, CropMirrorNormalizebatchPDLocalData *data)
{
	vx_status status = VX_SUCCESS;
 	size_t arr_size;
	vx_status copy_status;
    STATUS_ERROR_CHECK(vxQueryArray((vx_array)parameters[6], VX_ARRAY_ATTRIBUTE_NUMITEMS, &arr_size, sizeof(arr_size)));
	data->start_x = (vx_uint32 *)malloc(sizeof(vx_uint32) * arr_size);
	copy_status = vxCopyArrayRange((vx_array)parameters[6], 0, arr_size, sizeof(vx_uint32),data->start_x, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
    STATUS_ERROR_CHECK(vxQueryArray((vx_array)parameters[7], VX_ARRAY_ATTRIBUTE_NUMITEMS, &arr_size, sizeof(arr_size)));
	data->start_y = (vx_uint32 *)malloc(sizeof(vx_uint32) * arr_size);
	copy_status = vxCopyArrayRange((vx_array)parameters[7], 0, arr_size, sizeof(vx_uint32),data->start_y, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);

    STATUS_ERROR_CHECK(vxQueryArray((vx_array)parameters[8], VX_ARRAY_ATTRIBUTE_NUMITEMS, &arr_size, sizeof(arr_size)));
	data->mean = (vx_float32 *)malloc(sizeof(vx_float32) * arr_size);
	copy_status = vxCopyArrayRange((vx_array)parameters[8], 0, arr_size, sizeof(vx_float32),data->mean, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
    STATUS_ERROR_CHECK(vxQueryArray((vx_array)parameters[9], VX_ARRAY_ATTRIBUTE_NUMITEMS, &arr_size, sizeof(arr_size)));
	data->std_dev = (vx_float32 *)malloc(sizeof(vx_float32) * arr_size);
	copy_status = vxCopyArrayRange((vx_array)parameters[9], 0, arr_size, sizeof(vx_float32),data->std_dev, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
    
    STATUS_ERROR_CHECK(vxQueryArray((vx_array)parameters[10], VX_ARRAY_ATTRIBUTE_NUMITEMS, &arr_size, sizeof(arr_size)));
	data->mirror = (vx_uint32 *)malloc(sizeof(vx_uint32) * arr_size);
	copy_status = vxCopyArrayRange((vx_array)parameters[10], 0, arr_size, sizeof(vx_uint32),data->mirror, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
    STATUS_ERROR_CHECK(vxReadScalarValue((vx_scalar)parameters[11], &data->chnShift));
	STATUS_ERROR_CHECK(vxReadScalarValue((vx_scalar)parameters[12], &data->nbatchSize));
	STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[0], VX_IMAGE_HEIGHT, &data->maxSrcDimensions.height, sizeof(data->maxSrcDimensions.height)));
	STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[0], VX_IMAGE_WIDTH, &data->maxSrcDimensions.width, sizeof(data->maxSrcDimensions.width)));
	data->maxSrcDimensions.height = data->maxSrcDimensions.height / data->nbatchSize;
	STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[3], VX_IMAGE_HEIGHT, &data->maxDstDimensions.height, sizeof(data->maxDstDimensions.height)));
	STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[3], VX_IMAGE_WIDTH, &data->maxDstDimensions.width, sizeof(data->maxDstDimensions.width)));
	data->maxDstDimensions.height = data->maxDstDimensions.height / data->nbatchSize;
	data->srcDimensions = (RppiSize *)malloc(sizeof(RppiSize) * data->nbatchSize);
	data->dstDimensions = (RppiSize *)malloc(sizeof(RppiSize) * data->nbatchSize);
	Rpp32u *srcBatch_width = (Rpp32u *)malloc(sizeof(Rpp32u) * data->nbatchSize);
	Rpp32u *srcBatch_height = (Rpp32u *)malloc(sizeof(Rpp32u) * data->nbatchSize);
	Rpp32u *dstBatch_width = (Rpp32u *)malloc(sizeof(Rpp32u) * data->nbatchSize);
	Rpp32u *dstBatch_height = (Rpp32u *)malloc(sizeof(Rpp32u) * data->nbatchSize);
	copy_status = vxCopyArrayRange((vx_array)parameters[1], 0, data->nbatchSize, sizeof(Rpp32u),srcBatch_width, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
	copy_status = vxCopyArrayRange((vx_array)parameters[2], 0, data->nbatchSize, sizeof(Rpp32u),srcBatch_height, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
	copy_status = vxCopyArrayRange((vx_array)parameters[4], 0, data->nbatchSize, sizeof(Rpp32u),dstBatch_width, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
	copy_status = vxCopyArrayRange((vx_array)parameters[5], 0, data->nbatchSize, sizeof(Rpp32u),dstBatch_height, VX_READ_ONLY, VX_MEMORY_TYPE_HOST);
	for(int i = 0; i < data->nbatchSize; i++){
		data->srcDimensions[i].width = srcBatch_width[i];
		data->srcDimensions[i].height = srcBatch_height[i];
		data->dstDimensions[i].width = dstBatch_width[i];
		data->dstDimensions[i].height = dstBatch_height[i];
	}
	if(data->device_type == AGO_TARGET_AFFINITY_GPU) {
#if ENABLE_OPENCL
		STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[0], VX_IMAGE_ATTRIBUTE_AMD_OPENCL_BUFFER, &data->cl_pSrc, sizeof(data->cl_pSrc)));
		STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[3], VX_IMAGE_ATTRIBUTE_AMD_OPENCL_BUFFER, &data->cl_pDst, sizeof(data->cl_pDst)));
#endif
	}
	if(data->device_type == AGO_TARGET_AFFINITY_CPU) {
		STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[0], VX_IMAGE_ATTRIBUTE_AMD_HOST_BUFFER, &data->pSrc, sizeof(vx_uint8)));
		STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[3], VX_IMAGE_ATTRIBUTE_AMD_HOST_BUFFER, &data->pDst, sizeof(vx_uint8)));
	}
	return status; 
}

static vx_status VX_CALLBACK validateCropMirrorNormalizebatchPD(vx_node node, const vx_reference parameters[], vx_uint32 num, vx_meta_format metas[])
{
	vx_status status = VX_SUCCESS;
	vx_enum scalar_type;
	STATUS_ERROR_CHECK(vxQueryScalar((vx_scalar)parameters[11], VX_SCALAR_TYPE, &scalar_type, sizeof(scalar_type)));
 	if(scalar_type != VX_TYPE_UINT32) return ERRMSG(VX_ERROR_INVALID_TYPE, "validate: Paramter: #11 type=%d (must be size)\n", scalar_type);
	STATUS_ERROR_CHECK(vxQueryScalar((vx_scalar)parameters[12], VX_SCALAR_TYPE, &scalar_type, sizeof(scalar_type)));
 	if(scalar_type != VX_TYPE_UINT32) return ERRMSG(VX_ERROR_INVALID_TYPE, "validate: Paramter: #12 type=%d (must be size)\n", scalar_type);
	STATUS_ERROR_CHECK(vxQueryScalar((vx_scalar)parameters[13], VX_SCALAR_TYPE, &scalar_type, sizeof(scalar_type)));
 	if(scalar_type != VX_TYPE_UINT32) return ERRMSG(VX_ERROR_INVALID_TYPE, "validate: Paramter: #13 type=%d (must be size)\n", scalar_type);
	// Check for input parameters 
	vx_parameter input_param; 
	vx_image input; 
	vx_df_image df_image;
	input_param = vxGetParameterByIndex(node,0);
	STATUS_ERROR_CHECK(vxQueryParameter(input_param, VX_PARAMETER_ATTRIBUTE_REF, &input, sizeof(vx_image)));
	STATUS_ERROR_CHECK(vxQueryImage(input, VX_IMAGE_ATTRIBUTE_FORMAT, &df_image, sizeof(df_image))); 
	if(df_image != VX_DF_IMAGE_U8 && df_image != VX_DF_IMAGE_RGB) 
	{
		return ERRMSG(VX_ERROR_INVALID_FORMAT, "validate: CropMirrorNormalizebatchPD: image: #0 format=%4.4s (must be RGB2 or U008)\n", (char *)&df_image);
	}

	// Check for output parameters 
	vx_image output; 
	vx_df_image format; 
	vx_parameter output_param; 
	vx_uint32  height, width; 
	output_param = vxGetParameterByIndex(node,3);
	STATUS_ERROR_CHECK(vxQueryParameter(output_param, VX_PARAMETER_ATTRIBUTE_REF, &output, sizeof(vx_image))); 
	STATUS_ERROR_CHECK(vxQueryImage(output, VX_IMAGE_ATTRIBUTE_WIDTH, &width, sizeof(width))); 
	STATUS_ERROR_CHECK(vxQueryImage(output, VX_IMAGE_ATTRIBUTE_HEIGHT, &height, sizeof(height))); 
	STATUS_ERROR_CHECK(vxSetMetaFormatAttribute(metas[3], VX_IMAGE_ATTRIBUTE_WIDTH, &width, sizeof(width)));
	STATUS_ERROR_CHECK(vxSetMetaFormatAttribute(metas[3], VX_IMAGE_ATTRIBUTE_HEIGHT, &height, sizeof(height)));
	STATUS_ERROR_CHECK(vxSetMetaFormatAttribute(metas[3], VX_IMAGE_ATTRIBUTE_FORMAT, &df_image, sizeof(df_image)));
	vxReleaseImage(&input);
	vxReleaseImage(&output);
	vxReleaseParameter(&output_param);
	vxReleaseParameter(&input_param);
	return status;
}

static vx_status VX_CALLBACK processCropMirrorNormalizebatchPD(vx_node node, const vx_reference * parameters, vx_uint32 num) 
{
	RppStatus status = RPP_SUCCESS;
	CropMirrorNormalizebatchPDLocalData * data = NULL;
	STATUS_ERROR_CHECK(vxQueryNode(node, VX_NODE_LOCAL_DATA_PTR, &data, sizeof(data)));
	vx_df_image df_image = VX_DF_IMAGE_VIRT;
	STATUS_ERROR_CHECK(vxQueryImage((vx_image)parameters[0], VX_IMAGE_ATTRIBUTE_FORMAT, &df_image, sizeof(df_image)));

	if(data->device_type == AGO_TARGET_AFFINITY_GPU) {
#if ENABLE_OPENCL
		cl_command_queue handle = data->handle.cmdq;
		refreshCropMirrorNormalizebatchPD(node, parameters, num, data);
		if (df_image == VX_DF_IMAGE_U8 ){ 
 			status = rppi_crop_mirror_normalize_u8_pln1_batchPD_gpu((void *)data->cl_pSrc,data->srcDimensions,data->maxSrcDimensions,(void *)data->cl_pDst,data->dstDimensions,data->maxDstDimensions,data->start_x,data->start_y, data->mean, data->std_dev, data->mirror, data->chnShift ,data->nbatchSize,data->rppHandle);
		}
		else if(df_image == VX_DF_IMAGE_RGB) {
			status = rppi_crop_mirror_normalize_u8_pkd3_batchPD_gpu((void *)data->cl_pSrc,data->srcDimensions,data->maxSrcDimensions,(void *)data->cl_pDst,data->dstDimensions,data->maxDstDimensions,data->start_x,data->start_y, data->mean, data->std_dev, data->mirror, data->chnShift ,data->nbatchSize,data->rppHandle);
		}
		return status;
#endif
	}
	if(data->device_type == AGO_TARGET_AFFINITY_CPU) {
		refreshCropMirrorNormalizebatchPD(node, parameters, num, data);
		if (df_image == VX_DF_IMAGE_U8 ){
			status = rppi_crop_mirror_normalize_u8_pln1_batchPD_host(data->pSrc,data->srcDimensions,data->maxSrcDimensions,data->pDst,data->dstDimensions,data->maxDstDimensions,data->start_x,data->start_y,data->mean, data->std_dev, data->mirror, data->chnShift,data->nbatchSize,data->rppHandle);
		}
		else if(df_image == VX_DF_IMAGE_RGB) {
			status = rppi_crop_mirror_normalize_u8_pkd3_batchPD_host(data->pSrc,data->srcDimensions,data->maxSrcDimensions,data->pDst,data->dstDimensions,data->maxDstDimensions,data->start_x,data->start_y,data->mean, data->std_dev, data->mirror, data->chnShift,data->nbatchSize,data->rppHandle);
		}
		return status;
	}
}

static vx_status VX_CALLBACK initializeCropMirrorNormalizebatchPD(vx_node node, const vx_reference *parameters, vx_uint32 num) 
{
	CropMirrorNormalizebatchPDLocalData * data = new CropMirrorNormalizebatchPDLocalData;
	memset(data, 0, sizeof(*data));
#if ENABLE_OPENCL
	STATUS_ERROR_CHECK(vxQueryNode(node, VX_NODE_ATTRIBUTE_AMD_OPENCL_COMMAND_QUEUE, &data->handle.cmdq, sizeof(data->handle.cmdq)));
#endif
	STATUS_ERROR_CHECK(vxCopyScalar((vx_scalar)parameters[13], &data->device_type, VX_READ_ONLY, VX_MEMORY_TYPE_HOST));
	refreshCropMirrorNormalizebatchPD(node, parameters, num, data);
#if ENABLE_OPENCL
	if(data->device_type == AGO_TARGET_AFFINITY_GPU)
		rppCreateWithStreamAndBatchSize(&data->rppHandle, data->handle.cmdq, data->nbatchSize);
#endif
	if(data->device_type == AGO_TARGET_AFFINITY_CPU)
		rppCreateWithBatchSize(&data->rppHandle, data->nbatchSize);

	STATUS_ERROR_CHECK(vxSetNodeAttribute(node, VX_NODE_LOCAL_DATA_PTR, &data, sizeof(data)));
	return VX_SUCCESS;
}

static vx_status VX_CALLBACK uninitializeCropMirrorNormalizebatchPD(vx_node node, const vx_reference *parameters, vx_uint32 num)
{
	CropMirrorNormalizebatchPDLocalData * data; 
	STATUS_ERROR_CHECK(vxQueryNode(node, VX_NODE_LOCAL_DATA_PTR, &data, sizeof(data)));
#if ENABLE_OPENCL
	if(data->device_type == AGO_TARGET_AFFINITY_GPU)
		rppDestroyGPU(data->rppHandle);
#endif
	if(data->device_type == AGO_TARGET_AFFINITY_CPU)
		rppDestroyHost(data->rppHandle);
	delete(data);
	return VX_SUCCESS; 
}

vx_status CropMirrorNormalizePD_Register(vx_context context)
{
	vx_status status = VX_SUCCESS;
	// Add kernel to the context with callbacks
	vx_kernel kernel = vxAddUserKernel(context, "org.rpp.CropMirrorNormalizebatchPD",
		VX_KERNEL_RPP_CROPMIRRORNORMALIZEBATCHPD,
		processCropMirrorNormalizebatchPD,
		14,
		validateCropMirrorNormalizebatchPD,
		initializeCropMirrorNormalizebatchPD,
		uninitializeCropMirrorNormalizebatchPD);
	ERROR_CHECK_OBJECT(kernel);
	AgoTargetAffinityInfo affinity;
	vxQueryContext(context, VX_CONTEXT_ATTRIBUTE_AMD_AFFINITY,&affinity, sizeof(affinity));
#if ENABLE_OPENCL
	// enable OpenCL buffer access since the kernel_f callback uses OpenCL buffers instead of host accessible buffers
	vx_bool enableBufferAccess = vx_true_e;
	if(affinity.device_type == AGO_TARGET_AFFINITY_GPU)
		STATUS_ERROR_CHECK(vxSetKernelAttribute(kernel, VX_KERNEL_ATTRIBUTE_AMD_OPENCL_BUFFER_ACCESS_ENABLE, &enableBufferAccess, sizeof(enableBufferAccess)));
#else
	vx_bool enableBufferAccess = vx_false_e;
#endif
	if (kernel)
	{
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 0, VX_INPUT, VX_TYPE_IMAGE, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 1, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 2, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 3, VX_OUTPUT, VX_TYPE_IMAGE, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 4, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 5, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 6, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 7, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 8, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 9, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
        PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 10, VX_INPUT, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 11, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
    	PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 12, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(kernel, 13, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxFinalizeKernel(kernel));
	}
	if (status != VX_SUCCESS)
	{
	exit:	vxRemoveKernel(kernel);	return VX_FAILURE; 
 	}
	return status;
}
