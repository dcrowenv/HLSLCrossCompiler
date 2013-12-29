//
// Generated by Microsoft (R) HLSL Shader Compiler 9.30.9200.20499
//
//
///
// Buffer Definitions: 
//
// cbuffer $Globals
// {
//
//   float4x4 World;                    // Offset:    0 Size:    64 [unused]
//   float4x4 View;                     // Offset:   64 Size:    64 [unused]
//   float4x4 Projection;               // Offset:  128 Size:    64 [unused]
//   float InnerFactor;                 // Offset:  192 Size:     4
//      = 0x3f800000 
//   float OuterFactor;                 // Offset:  196 Size:     4
//      = 0x3f800000 
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// $Globals                          cbuffer      NA          NA    0        1
//
//
//
// Patch Constant signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TessFactor            0   x           0 QUADEDGE   float   x   
// SV_TessFactor            1   x           1 QUADEDGE   float   x   
// SV_TessFactor            2   x           2 QUADEDGE   float   x   
// SV_TessFactor            3   x           3 QUADEDGE   float   x   
// SV_InsideTessFactor      0   x           4  QUADINT   float   x   
// SV_InsideTessFactor      1   x           5  QUADINT   float   x   
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float   xyzw
// COLOR                    0   xyzw        1     NONE   float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0     NONE   float   xyzw
// COLOR                    0   xyzw        1     NONE   float   xyzw
//
// Tessellation Domain   # of control points
// -------------------- --------------------
// Quadrilateral                           4
//
// Tessellation Output Primitive  Partitioning Type 
// ------------------------------ ------------------
// Counter-Clockwise Triangles    Integer           
//
hs_5_0
hs_decls 
dcl_input_control_point_count 4
dcl_output_control_point_count 4
dcl_tessellator_domain domain_quad
dcl_tessellator_partitioning partitioning_integer
dcl_tessellator_output_primitive output_triangle_ccw
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer cb0[13], immediateIndexed
hs_control_point_phase 
dcl_input vOutputControlPointID
dcl_input v[4][0].xyzw
dcl_input v[4][1].xyzw
dcl_output o0.xyzw
dcl_output o1.xyzw
dcl_temps 2
mov r0.x, vOutputControlPointID
mov r1.xyzw, v[r0.x + 0][0].xyzw
mov r0.xyzw, v[r0.x + 0][1].xyzw
mov o0.xyzw, r1.xyzw
mov o1.xyzw, r0.xyzw
ret 
hs_join_phase 
dcl_output_siv o0.x, finalQuadUeq0EdgeTessFactor
dcl_output_siv o1.x, finalQuadVeq0EdgeTessFactor
dcl_output_siv o2.x, finalQuadUeq1EdgeTessFactor
dcl_output_siv o3.x, finalQuadVeq1EdgeTessFactor
dcl_output_siv o4.x, finalQuadUInsideTessFactor
dcl_output_siv o5.x, finalQuadVInsideTessFactor
dcl_temps 2
mov r0.x, cb0[12].x
mov r0.y, cb0[12].x
mov r0.z, cb0[12].y
mov r0.w, cb0[12].y
mov r1.x, cb0[12].y
mov r1.y, cb0[12].y
mov o0.x, r0.z
mov o1.x, r0.w
mov o2.x, r1.x
mov o3.x, r1.y
mov o4.x, r0.x
mov o5.x, r0.y
ret 
// Approximately 19 instruction slots used
