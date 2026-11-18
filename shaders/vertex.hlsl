struct Input
{
  float3 position : POSITION;
  float3 color : COLOR0;
};

struct Output
{
  float4 position : SV_Position;
  float3 color : COLOR0;
};

Output Main(Input input)
{
  Output output = (Output) 0;
  output.position = float4(input.position, 1.0);
  output.color = input.color;
  return output;
}