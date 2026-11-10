/*
 * Padding for the image decryption timing test: fills slot0 up to the reserve below.
 * Not needed for normal use, remove src/pad.c from CMakeLists.txt to disable it.
 */

#include <stdint.h>
#include <zephyr/devicetree.h>
#include <zephyr/toolchain.h>

#define SLOT0_SIZE DT_REG_SIZE(DT_NODELABEL(slot0_partition))

/* Application code (~41 KB at the time of writing), image header and TLVs, plus a small margin. */
#define PAD_RESERVE (44 * 1024)

#define PAD_SIZE (SLOT0_SIZE - PAD_RESERVE)

BUILD_ASSERT(PAD_SIZE % 16 == 0, "The image payload must be a multiple of the AES block size");

/* retain: nothing references the array, so --gc-sections would drop it otherwise. */
static const uint8_t pad_blob[PAD_SIZE] __used __attribute__((retain)) __aligned(16) = {1};
