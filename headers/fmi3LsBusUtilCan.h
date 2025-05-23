#ifndef fmi3LsBusUtilCan_h
#define fmi3LsBusUtilCan_h

/*
This header file contains utility macros to read and write FMI-LS-BUS
CAN specific bus operations from\to dedicated buffer variables.

This header file can be used when creating Network FMI-LS-BUS FMUs with CAN busses.

Copyright (C) 2023-2025 Modelica Association Project "FMI"
              All rights reserved.

This file is licensed by the copyright holders under the 2-Clause BSD License
(https://opensource.org/licenses/BSD-2-Clause):

----------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
----------------------------------------------------------------------------
*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "fmi3LsBusCan.h"
#include "fmi3LsBusUtil.h"

/**
 * \brief Creates a CAN transmit operation.
 *
 *  This macro can be used to create a CAN transmit operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *   
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ID          CAN message ID (\ref fmi3LsBusCanId).
 * \param[in] Ide         CAN message ID type (standard/extended) (\ref fmi3LsBusCanIde).
 * \param[in] Rtr         Remote Transmission Request (\ref fmi3LsBusCanRtr).
 * \param[in] DataLength  Message data length (\ref fmi3LsBusCanDataLength).
 * \param[in] Data        Message data (\ref fmi3LsBusCanDataLength).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CAN_TRANSMIT(BufferInfo, ID, Ide, Rtr, DataLength, Data)              \
    do                                                                                                  \
    {                                                                                                   \
        fmi3LsBusCanOperationCanTransmit _op;                                                           \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CAN_TRANSMIT;                                              \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) +                                          \
                            sizeof(fmi3LsBusCanId) +                                                    \
                            sizeof(fmi3LsBusCanIde) +                                                   \
                            sizeof(fmi3LsBusCanRtr) +                                                   \
                            sizeof(fmi3LsBusCanDataLength) +                                            \
                            (DataLength);                                                               \
        _op.id = (ID);                                                                                  \
        _op.ide = (Ide);                                                                                \
        _op.rtr = (Rtr);                                                                                \
                                                                                                        \
        _op.dataLength = (DataLength);                                                                  \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))              \
        {                                                                                               \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length - (DataLength));                     \
            (BufferInfo)->writePos += _op.header.length - (DataLength);                                 \
            memcpy((BufferInfo)->writePos, (Data), (DataLength));                                       \
            (BufferInfo)->writePos += (DataLength);                                                     \
            (BufferInfo)->status = fmi3True;                                                            \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            (BufferInfo)->status = fmi3False;                                                           \
        }                                                                                               \
    }                                                                                                   \
    while (0)

/**
 * \brief Creates a CAN FD transmit operation.
 *
 *  This macro can be used to create a CAN FD transmit operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ID          CAN message ID (\ref fmi3LsBusCanId).
 * \param[in] Ide         CAN message ID type (standard\extended) (\ref fmi3LsBusCanIde).
 * \param[in] Brs         Bit Rate Switch (\ref fmi3LsBusCanBrs).
 * \param[in] Esi         Error State Indicator (\ref fmi3LsBusCanEsi).
 * \param[in] DataLength  Message data length (\ref fmi3LsBusCanDataLength).
 * \param[in] Data        Message data (\ref fmi3LsBusCanDataLength).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CAN_FD_TRANSMIT(BufferInfo, ID, Ide, Brs, Esi, DataLength, Data)                \
    do                                                                                                            \
    {                                                                                                             \
        fmi3LsBusCanOperationCanFdTransmit _op;                                                                   \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CANFD_TRANSMIT;                                                      \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanId) + sizeof(fmi3LsBusCanIde) + \
                            sizeof(fmi3LsBusCanBrs) + sizeof(fmi3LsBusCanEsi) + sizeof(fmi3LsBusCanDataLength) +  \
                            (DataLength);                                                                         \
        _op.id = (ID);                                                                                            \
        _op.ide = (Ide);                                                                                          \
        _op.brs = (Brs);                                                                                          \
        _op.esi = (Esi);                                                                                          \
                                                                                                                  \
        _op.dataLength = (DataLength);                                                                            \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))                        \
        {                                                                                                         \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length - (DataLength));                               \
            (BufferInfo)->writePos += _op.header.length - (DataLength);                                           \
            memcpy((BufferInfo)->writePos, (Data), (DataLength));                                                 \
            (BufferInfo)->writePos += (DataLength);                                                               \
            (BufferInfo)->status = fmi3True;                                                                      \
        }                                                                                                         \
        else                                                                                                      \
        {                                                                                                         \
            (BufferInfo)->status = fmi3False;                                                                     \
        }                                                                                                         \
    }                                                                                                             \
    while (0)

/**
 * \brief Creates a CAN XL transmit operation.
 *
 *  This macro can be used to create a CAN XL transmit operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ID          CAN message ID (\ref fmi3LsBusCanId).
 * \param[in] Ide         CAN message ID type (standard/extended) (\ref fmi3LsBusCanIde).
 * \param[in] Sec         Simple Extended Content (\ref fmi3LsBusCanSec).
 * \param[in] Sdt         Service Data Unit Type (\ref fmi3LsBusCanSdt).
 * \param[in] VcId        Virtual CAN Network ID (\ref fmi3LsBusCanVcId).
 * \param[in] Af          Acceptance Field (\ref fmi3LsBusCanAf).
 * \param[in] DataLength  Message data length (\ref fmi3LsBusCanDataLength).
 * \param[in] Data        Message data (\ref fmi3LsBusCanDataLength).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CAN_XL_TRANSMIT(BufferInfo, ID, Ide, Sec, Sdt, VcId, Af, DataLength, Data)      \
    do                                                                                                            \
    {                                                                                                             \
        fmi3LsBusCanOperationCanXlTransmit _op;                                                                   \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CANXL_TRANSMIT;                                                      \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanId) + sizeof(fmi3LsBusCanIde) + \
                            sizeof(fmi3LsBusCanSec) + sizeof(fmi3LsBusCanSdt) + sizeof(fmi3LsBusCanVcId) +        \
                            sizeof(fmi3LsBusCanAf) + sizeof(fmi3LsBusCanDataLength) + (DataLength);             \
        _op.id = (ID);                                                                                            \
        _op.ide = (Ide);                                                                                          \
        _op.sec = (Sec);                                                                                          \
        _op.sdt = (Sdt);                                                                                          \
        _op.vcid = (VcId);                                                                                        \
        _op.af = (Af);                                                                                            \
                                                                                                                  \
        _op.dataLength = (DataLength);                                                                            \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))                        \
        {                                                                                                         \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length - (DataLength));                               \
            (BufferInfo)->writePos += _op.header.length - (DataLength);                                           \
            memcpy((BufferInfo)->writePos, (Data), (DataLength));                                                 \
            (BufferInfo)->writePos += (DataLength);                                                               \
            (BufferInfo)->status = fmi3True;                                                                      \
        }                                                                                                         \
        else                                                                                                      \
        {                                                                                                         \
            (BufferInfo)->status = fmi3False;                                                                     \
        }                                                                                                         \
    }                                                                                                             \
    while (0)

/**
 * \brief Creates a CAN confirm operation.
 *
 *  This macro can be used to create a CAN confirm operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ID          CAN message ID (\ref fmi3LsBusCanId).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CONFIRM(BufferInfo, ID)                                  \
    do                                                                                     \
    {                                                                                      \
        fmi3LsBusCanOperationConfirm _op;                                                  \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CONFIRM;                                      \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) +                             \
                            sizeof(fmi3LsBusCanId);                                        \
        _op.id = (ID);                                                                     \
                                                                                           \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos)) \
        {                                                                                  \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                       \
            (BufferInfo)->writePos += _op.header.length;                                   \
            (BufferInfo)->status = fmi3True;                                               \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (BufferInfo)->status = fmi3False;                                              \
        }                                                                                  \
    }                                                                                      \
    while (0)

/**
 * \brief Creates a CAN configuration operation for the baud rate setting.
 *
 *  This macro can be used to create a CAN configuration operation for the baud rate setting.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] BaudRate    The baud rate (\ref fmi3LsBusCanBaudrate).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CONFIGURATION_CAN_BAUDRATE(BufferInfo, BaudRate)                      \
    do                                                                                                  \
    {                                                                                                   \
        fmi3LsBusCanOperationConfiguration _op;                                                         \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CONFIGURATION;                                             \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) +                                          \
                            sizeof(fmi3LsBusCanConfigParameterType) +                                   \
                            sizeof(fmi3LsBusCanBaudrate);                                               \
        _op.parameterType = FMI3_LS_BUS_CAN_CONFIG_PARAM_TYPE_CAN_BAUDRATE;                             \
        _op.baudrate = (BaudRate);                                                                      \
                                                                                                        \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))              \
        {                                                                                               \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                                    \
            (BufferInfo)->writePos += _op.header.length;                                                \
            (BufferInfo)->status = fmi3True;                                                            \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            (BufferInfo)->status = fmi3False;                                                           \
        }                                                                                               \
    }                                                                                                   \
    while (0)

/**
 * \brief Creates a CAN configuration operation for the CAN FD baud rate setting.
 *
 *  This macro can be used to create a CAN configuration operation for the CAN FD baud rate setting.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] BaudRate    The baud rate (\ref fmi3LsBusCanBaudrate).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CONFIGURATION_CAN_FD_BAUDRATE(BufferInfo, BaudRate)                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        fmi3LsBusCanOperationConfiguration _op;                                                                        \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CONFIGURATION;                                                            \
        _op.header.length =                                                                                            \
            sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanConfigParameterType) + sizeof(fmi3LsBusCanBaudrate); \
        _op.parameterType = FMI3_LS_BUS_CAN_CONFIG_PARAM_TYPE_CANFD_BAUDRATE;                                          \
        _op.baudrate = (BaudRate);                                                                                     \
                                                                                                                       \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))                             \
        {                                                                                                              \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                                                   \
            (BufferInfo)->writePos += _op.header.length;                                                               \
            (BufferInfo)->status = fmi3True;                                                                           \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            (BufferInfo)->status = fmi3False;                                                                          \
        }                                                                                                              \
    }                                                                                                                  \
    while (0)

/**
 * \brief Creates a CAN configuration operation for the CAN XL baud rate setting.
 *
 *  This macro can be used to create a CAN configuration operation for the CAN XL baud rate setting.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] BaudRate    The baud rate (\ref fmi3LsBusCanBaudrate).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CONFIGURATION_CAN_XL_BAUDRATE(BufferInfo, BaudRate)                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        fmi3LsBusCanOperationConfiguration _op;                                                                        \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CONFIGURATION;                                                            \
        _op.header.length =                                                                                            \
            sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanConfigParameterType) + sizeof(fmi3LsBusCanBaudrate); \
        _op.parameterType = FMI3_LS_BUS_CAN_CONFIG_PARAM_TYPE_CANXL_BAUDRATE;                                          \
        _op.baudrate = (BaudRate);                                                                                     \
                                                                                                                       \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))                             \
        {                                                                                                              \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                                                   \
            (BufferInfo)->writePos += _op.header.length;                                                               \
            (BufferInfo)->status = fmi3True;                                                                           \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            (BufferInfo)->status = fmi3False;                                                                          \
        }                                                                                                              \
    }                                                                                                                  \
    while (0)

/**
 * \brief Creates a CAN configuration operation for the arbitration lost behavior setting.
 *
 *  This macro can be used to create a CAN configuration operation for the arbitration lost behavior setting.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo               Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ArbitrationLostBehavior  The arbitration lost behavior (\ref fmi3LsBusCanArbitrationLostBehavior).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_CONFIGURATION_ARBITRATION_LOST_BEHAVIOR(BufferInfo, ArbitrationLostBehavior)                        \
    do                                                                                                                                \
    {                                                                                                                                 \
        fmi3LsBusCanOperationConfiguration _op;                                                                                       \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_CONFIGURATION;                                                                           \
        _op.header.length =                                                                                                           \
            sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanConfigParameterType) + sizeof(fmi3LsBusCanArbitrationLostBehavior); \
        _op.parameterType = FMI3_LS_BUS_CAN_CONFIG_PARAM_TYPE_ARBITRATION_LOST_BEHAVIOR;                                              \
        _op.arbitrationLostBehavior = (ArbitrationLostBehavior);                                                                      \
                                                                                                                                      \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))                                            \
        {                                                                                                                             \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                                                                  \
            (BufferInfo)->writePos += _op.header.length;                                                                              \
            (BufferInfo)->status = fmi3True;                                                                                          \
        }                                                                                                                             \
        else                                                                                                                          \
        {                                                                                                                             \
            (BufferInfo)->status = fmi3False;                                                                                         \
        }                                                                                                                             \
    }                                                                                                                                 \
    while (0)

/**
 * \brief Creates a CAN arbitration lost operation.
 *
 *  This macro can be used to create a CAN arbitration lost operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ID          CAN message ID (\ref fmi3LsBusCanId).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_ARBITRATION_LOST(BufferInfo, ID)                         \
    do                                                                                     \
    {                                                                                      \
        fmi3LsBusCanOperationArbitrationLost _op;                                          \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_ARBITRATION_LOST;                             \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanId);     \
        _op.id = (ID);                                                                     \
                                                                                           \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos)) \
        {                                                                                  \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                       \
            (BufferInfo)->writePos += _op.header.length;                                   \
            (BufferInfo)->status = fmi3True;                                               \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (BufferInfo)->status = fmi3False;                                              \
        }                                                                                  \
    }                                                                                      \
    while (0)

/**
 * \brief Creates a CAN bus error operation.
 *
 *  This macro can be used to create a CAN bus error operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] ID          CAN message ID (\ref fmi3LsBusCanId).
 * \param[in] ErrorCode   Error Code (\ref fmi3LsBusCanErrorCode).
 * \param[in] ErrorFlag   Error Flag (\ref fmi3LsBusCanErrorFlag).
 * \param[in] IsSender    Is Sender (\ref fmi3LsBusCanIsSender).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_BUS_ERROR(BufferInfo, ID, ErrorCode, ErrorFlag, IsSender)        \
    do                                                                                             \
    {                                                                                              \
        fmi3LsBusCanOperationBusError _op;                                                         \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_BUS_ERROR;                                        \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanId) +            \
           sizeof(fmi3LsBusCanErrorCode) + sizeof(fmi3LsBusCanErrorFlag) +                         \
           sizeof(fmi3LsBusCanIsSender);                                                           \
        _op.id = (ID);                                                                             \
        _op.errorCode = (ErrorCode);                                                               \
        _op.errorFlag = (ErrorFlag);                                                               \
        _op.isSender = (IsSender);                                                                 \
                                                                                                   \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))         \
        {                                                                                          \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                               \
            (BufferInfo)->writePos += _op.header.length;                                           \
            (BufferInfo)->status = fmi3True;                                                       \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            (BufferInfo)->status = fmi3False;                                                      \
        }                                                                                          \
    }                                                                                              \
    while (0)

/**
 * \brief Creates a CAN status operation.
 *
 *  This macro can be used to create a CAN status operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 * \param[in] Status      Status Kind (\ref fmi3LsBusCanStatusKind).
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_STATUS(BufferInfo, Status)                                   \
    do                                                                                         \
    {                                                                                          \
        fmi3LsBusCanOperationStatus _op;                                                       \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_STATUS;                                           \
        _op.header.length = sizeof(fmi3LsBusOperationHeader) + sizeof(fmi3LsBusCanStatusKind); \
        _op.status = (Status);                                                                 \
                                                                                               \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos))     \
        {                                                                                      \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                           \
            (BufferInfo)->writePos += _op.header.length;                                       \
            (BufferInfo)->status = fmi3True;                                                   \
        }                                                                                      \
        else                                                                                   \
        {                                                                                      \
            (BufferInfo)->status = fmi3False;                                                  \
        }                                                                                      \
    }                                                                                          \
    while (0)

/**
 * \brief Creates a CAN wakeup operation.
 *
 *  This macro can be used to create a CAN wakeup operation.
 *  The arguments are serialized according to the FMI-LS-BUS specification and written to the buffer
 *  described by the argument 'BufferInfo'. If there is not enough buffer space available, the 'status'
 *  variable of the argument 'BufferInfo' is set to fmi3False.
 *
 * \param[in] BufferInfo  Pointer to \ref fmi3LsBusUtilBufferInfo.
 */
#define FMI3_LS_BUS_CAN_CREATE_OP_WAKEUP(BufferInfo)                                       \
    do                                                                                     \
    {                                                                                      \
        fmi3LsBusCanOperationWakeup _op;                                                   \
        _op.header.opCode = FMI3_LS_BUS_CAN_OP_WAKEUP;                                       \
        _op.header.length = sizeof(fmi3LsBusOperationHeader);                              \
                                                                                           \
        if (_op.header.length <= (fmi3UInt32)((BufferInfo)->end - (BufferInfo)->writePos)) \
        {                                                                                  \
            memcpy((BufferInfo)->writePos, &_op, _op.header.length);                       \
            (BufferInfo)->writePos += _op.header.length;                                   \
            (BufferInfo)->status = fmi3True;                                               \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (BufferInfo)->status = fmi3False;                                              \
        }                                                                                  \
    }                                                                                      \
    while (0)

#ifdef __cplusplus
} /* end of extern "C" { */
#endif


#endif /* fmi3LsBusUtilCan_h */
