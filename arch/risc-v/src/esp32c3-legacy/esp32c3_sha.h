/****************************************************************************
 * arch/risc-v/src/esp32c3-legacy/esp32c3_sha.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#ifndef __ARCH_RISCV_SRC_ESP32C3_LEGACY_ESP32C3_SHA_H
#define __ARCH_RISCV_SRC_ESP32C3_LEGACY_ESP32C3_SHA_H

#include <nuttx/config.h>
#include <stdint.h>

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

enum esp32c3_sha_type_e
{
    ESP32C3_SHA1_1 = 0,
    ESP32C3_SHA2_224,
    ESP32C3_SHA2_256,
    ESP32C3_SHA3_384,
    ESP32C3_SHA3_512,
    ESP32C3_SHA_TYPE_MAX
};

enum esp32c3_sha_state_e
{
    ESP32C3_SHA_STATE_INIT,
    ESP32C3_SHA_STATE_IN_PROCESS
};

/* SHA-1 context structure */

struct esp32c3_sha1_context_s
{
    uint32_t total[2];          /* number of bytes processed  */
    uint32_t state[5];          /* intermediate digest state  */
    unsigned char buffer[64];   /* data block being processed */
    bool first_block;           /* if first then true else false */
    enum esp32c3_sha_type_e mode;
    enum esp32c3_sha_state_e sha_state;
};

/* SHA-256 context structure */

struct esp32c3_sha256_context_s
{
    uint32_t total[2];          /* number of bytes processed  */
    uint32_t state[8];          /* intermediate digest state  */
    unsigned char buffer[64];   /* data block being processed */
    bool first_block;           /* if first then true, else false */
    enum esp32c3_sha_type_e mode;
    enum esp32c3_sha_state_e sha_state;
};

/* SHA-512 context structure */

struct esp32c3_sha512_context_s
{
    uint64_t        total[2];       /* number of bytes processed  */
    uint64_t        state[8];       /* intermediate digest state  */
    uint8_t         buffer[128];    /* data block being processed */

    bool first_block;               /* if first then true, else false */
    enum esp32c3_sha_type_e mode;
    enum esp32c3_sha_state_e sha_state;
};

/****************************************************************************
 * Name: esp32c3_sha_init
 *
 * Description:
 *   Initialize ESP32-C3 SHA hardware.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   OK is returned on success. Otherwise, a negated errno value is returned.
 *
 ****************************************************************************/

int esp32c3_sha_init(void);

/****************************************************************************
 * Name: esp32c3_sha1_init
 *
 * Description:
 *   Initializes a SHA-1 context.
 *
 * Input Parameters:
 *   ctx      - The SHA-1 context to initialize
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

void esp32c3_sha1_init(struct esp32c3_sha1_context_s *ctx);

/****************************************************************************
 * Name: esp32c3_sha1_starts
 *
 * Description:
 *   Starts a SHA-1 checksum calculation.
 *
 * Input Parameters:
 *   ctx      - The SHA-1 context to initialize
 *
 * Returned Value:
 *   OK is returned on success.
 *
 ****************************************************************************/

int esp32c3_sha1_starts(struct esp32c3_sha1_context_s *ctx);

/****************************************************************************
 * Name: esp32c3_sha1_update
 *
 * Description:
 *   Feeds an input buffer into an ongoing SHA-1 checksum calculation.
 *
 * Input Parameters:
 *   ctx      - The SHA-1 context to use
 *   input    - The buffer holding the input data
 *   ilen     - The length of the input data in Bytes
 *
 * Returned Value:
 *   OK is returned on success.
 *   Otherwise, a negated errno value is returned.
 *
 ****************************************************************************/

int esp32c3_sha1_update(struct esp32c3_sha1_context_s *ctx,
                        const unsigned char *input,
                        size_t ilen);

/****************************************************************************
 * Name: esp32c3_sha1_finish
 *
 * Description:
 *   Finishes the SHA-1 operation,
 *   and writes the result to the output buffer.
 *
 * Input Parameters:
 *   ctx      - The SHA-1 context to use
 *   output   - The SHA-1 checksum result
 *
 * Returned Value:
 *   OK is returned on success.
 *   Otherwise, a negated errno value is returned.
 *
 ****************************************************************************/

int esp32c3_sha1_finish(struct esp32c3_sha1_context_s *ctx,
                        unsigned char output[20]);

/****************************************************************************
 * Name: esp32c3_sha256_init
 *
 * Description:
 *   Initializes a SHA-256 context.
 *
 * Input Parameters:
 *   ctx      - The SHA-256 context to initialize
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

void esp32c3_sha256_init(struct esp32c3_sha256_context_s *ctx);

/****************************************************************************
 * Name: esp32c3_sha256_starts
 *
 * Description:
 *   Starts a SHA-224 or SHA-256 checksum calculation.
 *
 * Input Parameters:
 *   ctx      - The SHA-256 context to initialize
 *   is224    - Determines which function to use
 *
 * Returned Value:
 *   OK is returned on success.
 *
 ****************************************************************************/

int esp32c3_sha256_starts(struct esp32c3_sha256_context_s *ctx, bool is224);

/****************************************************************************
 * Name: esp32c3_sha256_update
 *
 * Description:
 *   Feeds an input buffer into an ongoing SHA-224 or SHA-256
 *   checksum calculation.
 *
 * Input Parameters:
 *   ctx      - The SHA-256 context to use
 *   input    - The buffer holding the input data
 *   ilen     - The length of the input data in Bytes
 *
 * Returned Value:
 *   OK is returned on success.
 *   Otherwise, a negated errno value is returned.
 *
 ****************************************************************************/

int esp32c3_sha256_update(struct esp32c3_sha256_context_s *ctx,
                          const unsigned char *input,
                          size_t ilen);

/****************************************************************************
 * Name: esp32c3_sha256_finish
 *
 * Description:
 *   Finishes the SHA-224 or SHA-256 operation, and writes the result to
 *   the output buffer.
 *
 * Input Parameters:
 *   ctx      - The SHA-256 context to use
 *   output   - The SHA-256 checksum result
 *
 * Returned Value:
 *   OK is returned on success.
 *   Otherwise, a negated errno value is returned.
 *
 ****************************************************************************/

int esp32c3_sha256_finish(struct esp32c3_sha256_context_s *ctx,
                          unsigned char output[32]);

#ifdef __cplusplus
}
#endif
#undef EXTERN

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_RISCV_SRC_ESP32C3_LEGACY_ESP32C3_SHA_H */
