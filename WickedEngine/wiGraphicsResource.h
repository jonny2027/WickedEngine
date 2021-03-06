#ifndef _GRAPHICSRESOURCE_H_
#define _GRAPHICSRESOURCE_H_

#include "CommonInclude.h"
#include "wiGraphicsDescriptors.h"

#include <vector>

namespace wiGraphicsTypes
{
	typedef uint64_t wiCPUHandle;
	static const wiCPUHandle WI_NULL_HANDLE = 0;

	class GraphicsDevice;

	struct GraphicsDeviceChild
	{
		GraphicsDevice* device = nullptr;
		void Register(GraphicsDevice* dev) { device = dev; }
	};

	struct ShaderByteCode
	{
		BYTE* data;
		size_t size;
		ShaderByteCode() :data(nullptr), size(0) {}
		~ShaderByteCode() { SAFE_DELETE_ARRAY(data); }
	};

	struct VertexShader : public GraphicsDeviceChild
	{
		VertexShader();
		~VertexShader();

		ShaderByteCode code;
		wiCPUHandle resource = WI_NULL_HANDLE;
	};

	struct PixelShader : public GraphicsDeviceChild
	{
		PixelShader();
		~PixelShader();

		ShaderByteCode code;
		wiCPUHandle resource = WI_NULL_HANDLE;
	};

	struct GeometryShader : public GraphicsDeviceChild
	{
		GeometryShader();
		~GeometryShader();

		ShaderByteCode code;
		wiCPUHandle resource = WI_NULL_HANDLE;
	};

	struct HullShader : public GraphicsDeviceChild
	{
		HullShader();
		~HullShader();

		ShaderByteCode code;
		wiCPUHandle resource = WI_NULL_HANDLE;
	};

	struct DomainShader : public GraphicsDeviceChild
	{
		DomainShader();
		~DomainShader();

		ShaderByteCode code;
		wiCPUHandle resource = WI_NULL_HANDLE;
	};

	struct ComputeShader : public GraphicsDeviceChild
	{
		ComputeShader();
		~ComputeShader();

		ShaderByteCode code;
		wiCPUHandle resource = WI_NULL_HANDLE;
	};

	struct Sampler : public GraphicsDeviceChild
	{
		wiCPUHandle resource = WI_NULL_HANDLE;
		SamplerDesc desc;

		Sampler();
		~Sampler();

		bool IsValid() { return resource != WI_NULL_HANDLE; }
		const SamplerDesc& GetDesc() const { return desc; }
	};

	struct GPUResource : public GraphicsDeviceChild
	{
		enum GPU_RESOURCE_TYPE
		{
			BUFFER,
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D,
			UNKNOWN_TYPE,
		} type = UNKNOWN_TYPE;
		inline bool IsTexture() const { return type == TEXTURE_1D || type == TEXTURE_2D || type == TEXTURE_3D; }
		inline bool IsBuffer() const { return type == BUFFER; }

		wiCPUHandle SRV = WI_NULL_HANDLE;			// main resource SRV
		std::vector<wiCPUHandle> additionalSRVs;	// can be used for sub-resources if requested

		wiCPUHandle UAV = WI_NULL_HANDLE;			// main resource UAV
		std::vector<wiCPUHandle> additionalUAVs;	// can be used for sub-resources if requested

		wiCPUHandle resource;
		wiCPUHandle resourceMemory;

		GPUResource();
		virtual ~GPUResource();
	};

	struct GPUBuffer : public GPUResource
	{
		wiCPUHandle CBV = WI_NULL_HANDLE;
		GPUBufferDesc desc;

		GPUBuffer();
		virtual ~GPUBuffer();

		bool IsValid() { return resource != WI_NULL_HANDLE; }
		const GPUBufferDesc& GetDesc() const { return desc; }
	};

	struct VertexLayout : public GraphicsDeviceChild
	{
		wiCPUHandle	resource = WI_NULL_HANDLE;

		std::vector<VertexLayoutDesc> desc;

		VertexLayout();
		~VertexLayout();
	};

	struct BlendState : public GraphicsDeviceChild
	{
		wiCPUHandle resource = WI_NULL_HANDLE;
		BlendStateDesc desc;

		BlendState();
		~BlendState();

		const BlendStateDesc& GetDesc() const { return desc; }
	};

	struct DepthStencilState : public GraphicsDeviceChild
	{
		wiCPUHandle resource = WI_NULL_HANDLE;
		DepthStencilStateDesc desc;

		DepthStencilState();
		~DepthStencilState();

		const DepthStencilStateDesc& GetDesc() const { return desc; }
	};

	struct RasterizerState : public GraphicsDeviceChild
	{
		wiCPUHandle resource = WI_NULL_HANDLE;
		RasterizerStateDesc desc;

		RasterizerState();
		~RasterizerState();

		const RasterizerStateDesc& GetDesc() const { return desc; }
	};

	struct Texture : public GPUResource
	{
		TextureDesc	desc;
		wiCPUHandle	RTV = WI_NULL_HANDLE;
		std::vector<wiCPUHandle> additionalRTVs;
		bool independentRTVArraySlices = false;
		bool independentRTVCubemapFaces = false;
		bool independentSRVArraySlices = false;
		bool independentSRVMIPs = false;
		bool independentUAVMIPs = false;

		const TextureDesc& GetDesc() const { return desc; }

		Texture();
		virtual ~Texture();

		// if true, then each array slice will get a unique rendertarget
		void RequestIndependentRenderTargetArraySlices(bool value);
		// if true, then each face of the cubemap will get a unique rendertarget
		void RequestIndependentRenderTargetCubemapFaces(bool value);
		// if true, then each array slice will get a unique shader resource
		void RequestIndependentShaderResourceArraySlices(bool value);
		// if true, then each miplevel will get unique shader resource
		void RequestIndependentShaderResourcesForMIPs(bool value);
		// if true, then each miplevel will get unique unordered access resource
		void RequestIndependentUnorderedAccessResourcesForMIPs(bool value);
	};

	struct Texture1D : public Texture
	{
		Texture1D();
		virtual ~Texture1D();
	};

	struct Texture2D : public Texture
	{
		wiCPUHandle	DSV = WI_NULL_HANDLE;
		std::vector<wiCPUHandle> additionalDSVs;

		Texture2D();
		virtual ~Texture2D();
	};

	struct Texture3D : public Texture
	{
		Texture3D();
		virtual ~Texture3D();
	};




	struct GPUQuery : public GraphicsDeviceChild
	{
		wiCPUHandle	resource;
		GPUQueryDesc desc;

		GPUQuery();
		virtual ~GPUQuery();

		bool IsValid() { return resource != WI_NULL_HANDLE; }
		const GPUQueryDesc& GetDesc() const { return desc; }
	};


	struct GraphicsPSO : public GraphicsDeviceChild
	{
		wiCPUHandle	pipeline;
		GraphicsPSODesc desc;

		const GraphicsPSODesc& GetDesc() const { return desc; }

		GraphicsPSO();
		~GraphicsPSO();
	};
	struct ComputePSO : public GraphicsDeviceChild
	{
		wiCPUHandle	pipeline;
		ComputePSODesc desc;

		const ComputePSODesc& GetDesc() const { return desc; }

		ComputePSO();
		~ComputePSO();
	};

}

#endif // _GRAPHICSRESOURCE_H_
