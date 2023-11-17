
#include <string.h>
#ifdef DEBUG_PRINTF
#include <stdio.h>
#endif

#define RST_SOFTCORE_ADDR   0x00A0010000
#define ITCM_SOFTCORE_ADDR  0x00B0000000
#define SHMEM_SOFTCORE_ADDR 0x00A0030000

//TODO: Need a way of loading binary instead of being in the same mem of the CA.
extern char cm1_bin_start;
extern char cm1_bin_end;

// Function to load a binary into the enclave
int load_binary_to_enclave(void) {
  uint32_t *itcm_addr = (uint32_t *) ITCM_SOFTCORE_ADDR;
  // Get the start addr and the size of the binary
  uint32_t *addr_bin = (uint32_t *) &cm1_bin_start;
  const uint32_t bin_size = &cm1_bin_end - &cm1_bin_start;
  /* Copy the binary to the ITCM memory */
  for(int i=0;i<bin_size>>2;i++) {
      *(volatile uint32_t *)(itcm_addr+i) = *(addr_bin+i);
  }

  /* Reset the enclave */
  *(volatile uint32_t *)RST_SOFTCORE_ADDR = (uint32_t) 0x0;
  *(volatile uint32_t *)RST_SOFTCORE_ADDR = (uint32_t) 0x1;
  #ifdef DEBUG_PRINTF
  printf("DBG::flash of the enclave, done!\n");
  #endif
  return TEEC_SUCCESS;
}
