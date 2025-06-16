public class Memory {
      static void memcpy(byte[] dest, byte[] src, int num) {
        for (int i = 0; i < num; i++) {
          dest[i] = src[i];
        }
      }
    }