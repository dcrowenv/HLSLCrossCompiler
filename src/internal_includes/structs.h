#ifndef STRUCTS_H
#define STRUCTS_H

#include "hlslcc.h"
#include "bstrlib.h"

#include "internal_includes/tokens.h"
#include "internal_includes/reflect.h"

enum{ MAX_SUB_OPERANDS = 3};

typedef struct Operand_TAG
{
    int iExtended;
    OPERAND_TYPE eType;
    OPERAND_MODIFIER eModifier;
    OPERAND_MIN_PRECISION eMinPrecision;
    int iIndexDims;
    int indexRepresentation[4];
    int writeMask;
    int iGSInput;
    int iWriteMaskEnabled;

    int iNumComponents;

    OPERAND_4_COMPONENT_SELECTION_MODE eSelMode;
    uint32_t ui32CompMask;
    uint32_t ui32Swizzle;
    uint32_t aui32Swizzle[4];

    uint32_t aui32ArraySizes[3];
    uint32_t ui32RegisterNumber;
    //If eType is OPERAND_TYPE_IMMEDIATE32
    float afImmediates[4];
    //If eType is OPERAND_TYPE_IMMEDIATE64
    double adImmediates[4];

	int iIntegerImmediate;

    SPECIAL_NAME eSpecialName;
    char pszSpecialName[64];

    OPERAND_INDEX_REPRESENTATION eIndexRep[3];

    struct Operand_TAG* psSubOperand[MAX_SUB_OPERANDS];

	//One type for each component.
	SHADER_VARIABLE_TYPE aeDataType[4];

#ifdef _DEBUG
    uint64_t id;
#endif
} Operand;

typedef struct Instruction_TAG
{
    OPCODE_TYPE eOpcode;
    INSTRUCTION_TEST_BOOLEAN eBooleanTestType;
	COMPARISON_DX9 eDX9TestType;
    uint32_t ui32SyncFlags;
    uint32_t ui32NumOperands;
    Operand asOperands[6];
    uint32_t bSaturate;
    uint32_t ui32FuncIndexWithinInterface;

    int bAddressOffset;
    int iUAddrOffset;
    int iVAddrOffset;
    int iWAddrOffset;

#ifdef _DEBUG
    uint64_t id;
#endif
} Instruction;

static enum{ MAX_IMMEDIATE_CONST_BUFFER_VEC4_SIZE = 1024};

typedef struct ICBVec4_TAG {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} ICBVec4;

typedef struct Declaration_TAG
{
    OPCODE_TYPE eOpcode;

    uint32_t ui32NumOperands;

    Operand asOperands[2];

	ICBVec4 asImmediateConstBuffer[MAX_IMMEDIATE_CONST_BUFFER_VEC4_SIZE];
    //The declaration can set one of these
    //values depending on the opcode.
    union {
        uint32_t ui32GlobalFlags;
        uint32_t ui32NumTemps;
        RESOURCE_DIMENSION eResourceDimension;
        INTERPOLATION_MODE eInterpolation;
        PRIMITIVE_TOPOLOGY eOutputPrimitiveTopology;
        PRIMITIVE eInputPrimitive;
        uint32_t ui32MaxOutputVertexCount;
        TESSELLATOR_DOMAIN eTessDomain;
        TESSELLATOR_PARTITIONING eTessPartitioning;
        TESSELLATOR_OUTPUT_PRIMITIVE eTessOutPrim;
        uint32_t aui32WorkGroupSize[3];
        //Fork phase index followed by the instance count.
        uint32_t aui32HullPhaseInstanceInfo[2];
        float fMaxTessFactor;
        uint32_t ui32IndexRange;

        struct Interface_TAG
        {
            uint32_t ui32InterfaceID;
            uint32_t ui32NumFuncTables;
            uint32_t ui32ArraySize;
        } interface;
    } value;

    struct UAV_TAG
    {
        uint32_t ui32GloballyCoherentAccess;
        uint32_t ui32BufferSize;
		uint8_t bCounter;
    } sUAV;

    uint32_t ui32TableLength;

	uint32_t ui32IsShadowTex;

} Declaration;

static enum {MAX_TEMP_VEC4 = 512};

typedef struct Shader_TAG
{
    uint32_t ui32MajorVersion;
    uint32_t ui32MinorVersion;
    SHADER_TYPE eShaderType;

    GLLang eTargetLanguage;

    //DWORDs in program code, including version and length tokens.
    uint32_t ui32ShaderLength;

    uint32_t ui32DeclCount;
    Declaration* psDecl;

    //Instruction* functions;//non-main subroutines

    uint32_t aui32FuncTableToFuncPointer[MAX_FUNCTION_TABLES];//FIXME dynamic alloc
    uint32_t aui32FuncBodyToFuncTable[MAX_FUNCTION_BODIES];

    struct {
        uint32_t aui32FuncBodies[MAX_FUNCTION_BODIES];
    }funcTable[MAX_FUNCTION_TABLES];

    struct {
        uint32_t aui32FuncTables[MAX_FUNCTION_TABLES];
        uint32_t ui32NumBodiesPerTable;
    }funcPointer[MAX_FUNCTION_POINTERS];

    uint32_t ui32NextClassFuncName[MAX_CLASS_TYPES];

    uint32_t ui32InstCount;
    Instruction* psInst;

    const uint32_t* pui32FirstToken;//Reference for calculating current position in token stream.

	//Hull shader declarations and instructions.
	//psDecl, psInst are null for hull shaders.
	uint32_t ui32HSDeclCount;
	Declaration* psHSDecl;

	uint32_t ui32HSControlPointDeclCount;
	Declaration* psHSControlPointPhaseDecl;

	uint32_t ui32HSControlPointInstrCount;
	Instruction* psHSControlPointPhaseInstr;

    uint32_t ui32ForkPhaseCount;

	uint32_t aui32HSForkDeclCount[MAX_FORK_PHASES];
	Declaration* apsHSForkPhaseDecl[MAX_FORK_PHASES];

	uint32_t aui32HSForkInstrCount[MAX_FORK_PHASES];
	Instruction* apsHSForkPhaseInstr[MAX_FORK_PHASES];

	uint32_t ui32HSJoinDeclCount;
	Declaration* psHSJoinPhaseDecl;

	uint32_t ui32HSJoinInstrCount;
	Instruction* psHSJoinPhaseInstr;

    ShaderInfo sInfo;

	int abScalarInput[MAX_SHADER_VEC4_INPUT];

    int aIndexedOutput[MAX_SHADER_VEC4_OUTPUT];

    int aIndexedInput[MAX_SHADER_VEC4_INPUT];
    int aIndexedInputParents[MAX_SHADER_VEC4_INPUT];

    RESOURCE_DIMENSION aeResourceDims[MAX_TEXTURES];

    int aiInputDeclaredSize[MAX_SHADER_VEC4_INPUT];

    int aiOutputDeclared[MAX_SHADER_VEC4_OUTPUT];

    //Does not track built-in inputs.
    int abInputReferencedByInstruction[MAX_SHADER_VEC4_INPUT];

	int aiOpcodeUsed[NUM_OPCODES];

} Shader;

static const uint32_t MAIN_PHASE = 0;
static const uint32_t HS_FORK_PHASE = 1;
static const uint32_t HS_CTRL_POINT_PHASE = 2;
static const uint32_t HS_JOIN_PHASE = 3;
static enum{ NUM_PHASES = 4};

typedef struct HLSLCrossCompilerContext_TAG
{
    bstring glsl;
	bstring earlyMain;//Code to be inserted at the start of main()
    bstring postShaderCode[NUM_PHASES];//End of main or before emit()

    bstring* currentGLSLString;//either glsl or earlyMain

    int havePostShaderCode[NUM_PHASES];
    uint32_t currentPhase;

    int indent;
    unsigned int flags;
    Shader* psShader;
    GLSLCrossDependencyData* psDependencies;
} HLSLCrossCompilerContext;

#endif
