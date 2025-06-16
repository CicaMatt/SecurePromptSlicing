public class MemoryCopy {
     
        private void copyMemory(long dest, long src, long numBytes) {
          for (int i = 0; i < numBytes; i++) {
            // Get byte from source and put it in the destination
            *((char*)dest + i) = *((char*)src + i);
          }
        }
     }