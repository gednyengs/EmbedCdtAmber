#ifndef AMBERM3VX_HAL_CGRA_H
#define AMBERM3VX_HAL_CGRA_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Constant Definitions *******************************/

#define GLC_REG_BASE_ADDR           AMBERM3V1_CGRA_GLC_BASE
#define GLB_REG_BASE_ADDR           (GLC_REG_BASE_ADDR + (1 << 12))

/************************* Type Definitions ***********************************/


/************************* Macro Definitions **********************************/

#define HAL_Cgra_WriteReg(BaseAddr, Offset, Data) \
  HAL_Out32((BaseAddr) + (Offset), (Data))

#define HAL_Cgra_ReadReg(BaseAddr, Offset) \
  HAL_In32((BaseAddr) + (Offset))

/************************* Function Prototypes ********************************/

/**
 * Write to Global Buffer Register
 * @param RegOffset The offset of the register to write to
 * @Value The data to write to the register
 *
 * @return N/A
 */
void HAL_Cgra_Glb_WriteReg(u32 RegOffset, u32 Value);

/**
 * Read from a Global Buffer Register
 * @param RegOffset The offset of the register to read
 *
 * @return The register value
 */
u32 HAL_Cgra_Glb_ReadReg(u32 RegOffset);

/**
 * Write to Global Controller Register
 * @param RegOffset The offset of the register to write to
 * @Value The data to write to the register
 *
 * @return N/A
 */
void HAL_Cgra_Glc_WriteReg(u32 RegOffset, u32 Value);

/**
 * Read from a Global Controller Register
 * @param RegOffset The offset of the register to read
 *
 * @return The register value
 */
u32 HAL_Cgra_Glc_ReadReg(u32 RegOffset);

/**
 * Write to CGRA Tile Register
 * @param RegOffset The offset of the register to write to
 * @Value The data to write to the register
 *
 * @return N/A
 */
void HAL_Cgra_Tile_WriteReg(u32 RegOffset, u32 Value);

/**
 * Read from a CGRA Tile Register
 * @param RegOffset The offset of the register to read
 *
 * @return The register value
 */
u32 HAL_Cgra_Tile_ReadReg(u32 RegOffset);


#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_CGRA_H */
