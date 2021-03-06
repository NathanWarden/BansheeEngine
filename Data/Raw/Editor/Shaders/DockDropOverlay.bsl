Parameters =
{
	float	invViewportWidth;
	float	invViewportHeight;
	
	color		tintColor;
	color		highlightColor;
	color		highlightActive;
};

Technique =
{
	Language = "HLSL11";
	
	Pass =
	{
		Target = 
		{
			Blend = true;
			Color = { SRCA, SRCIA, ADD };
		};
		
		DepthRead = false;
		DepthWrite = false;
		
		Vertex =
		{
			float invViewportWidth;
			float invViewportHeight;

			float4 tintColor;
			float4 highlightColor;
			float4 highlightActive;

			void main(
			in float2 inPos : POSITION,
			in float4 color : COLOR0,
			out float4 oPosition : SV_Position,
			out float4 oColor : COLOR0)
			{
				float tfrmdX = -1.0f + (inPos.x * invViewportWidth);
				float tfrmdY = 1.0f - (inPos.y * invViewportHeight);

				oPosition = float4(tfrmdX, tfrmdY, 0, 1);

				float4 highlight = highlightActive * color;
				float highlightSum = highlight.x + highlight.y + highlight.z + highlight.a;

				oColor = (1.0f - highlightSum) * tintColor + highlightSum * highlightColor;
			}
		};
		
		Fragment =
		{
			float4 main(in float4 inPos : SV_Position, in float4 color : COLOR0) : SV_Target
			{
				return color;
			}	
		};
	};
};

Technique =
{
	Language = "GLSL";
	
	Pass =
	{
		Target = 
		{
			Blend = true;
			Color = { SRCA, SRCIA, ADD };
		};
		
		DepthRead = false;
		DepthWrite = false;
		
		Vertex =
		{
			layout(location = 0) in vec2 bs_position;
			layout(location = 1) in vec4 bs_color0;
			
			layout(location = 0) out vec4 color0;
			
			out gl_PerVertex
			{
				vec4 gl_Position;
			};			
			
			layout(binding = 0) uniform VertUBO
			{
				float invViewportWidth;
				float invViewportHeight;

				vec4 tintColor;
				vec4 highlightColor;
				vec4 highlightActive;
			};

			void main()
			{
				float tfrmdX = -1.0f + (bs_position.x * invViewportWidth);
				float tfrmdY = 1.0f - (bs_position.y * invViewportHeight);

				gl_Position = vec4(tfrmdX, tfrmdY, 0, 1);

				vec4 highlight = highlightActive * bs_color0;
				float highlightSum = highlight.x + highlight.y + highlight.z + highlight.w;

				color0 = (1.0f - highlightSum) * tintColor + highlightSum * highlightColor;
			}
		};
		
		Fragment =
		{
			layout(location = 0) in vec4 color0;
			layout(location = 0) out vec4 fragColor;

			void main()
			{
				fragColor = color0;
			}
		};
	};
};