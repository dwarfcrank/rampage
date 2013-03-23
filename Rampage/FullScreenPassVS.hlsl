// This vertex shader generates the vertices for a triangle covering the whole screen.
// The vertices are generated on the fly and no vertex/index buffers are necessary.
float4 main(uint Index : SV_VertexID) : SV_POSITION
{
    switch(Index)
    {
    case 0:
        // Upper left corner
        return float4(-1.0f, 3.0f, 0.5f, 1.0f);
    case 1:
        // Lower right corner
        return float4(3.0f, -1.0f, 0.5f, 1.0f);
    case 2:
        // Lower left corner
        return float4(-1.0f, -1.0f, 0.5f, 1.0f);
        
    default:
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }
}