// This is a dummy shader used for validating the input layout.
// It serves no other purpose.

struct MeshInput
{
    float3 pos : POSITION;
};

float4 main( MeshInput input ) : SV_POSITION
{
    return float4(input.pos, 1.0);
}