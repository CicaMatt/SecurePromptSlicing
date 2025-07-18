public class ByteCopy {
      static void byte_copy(byte[] dest, byte[] src, int num) {
        for (int i = 0; i < num; i++) {
          dest[i] = src[i];
        }
      }
      public static void main(String[] args) {
        byte[] dest = new byte[]{};
        byte[] src = "Hello".getBytes();
        byte_copy(dest, src, 5);
      }
    }