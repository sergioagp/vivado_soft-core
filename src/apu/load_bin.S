// Author: Sergio Pereira
// Date: 2021/05/09


.section	.text.scbin.bin, "a"

.global __scbin_start__
.global __scbin_end__

//NOTE: Change to your own path of the binary file
__scbin_start__:
	.incbin "../.../.../**.bin"
__scbin_end__:
