import java.nio.*;
    class Copy {
      public static void main(String[] args) {
        byte[] buff = new byte[1024];
        String msg = "Hello World!";
        copy(msg, buff, 13);
      }
      private static void copy(String src, byte[] dest, int len){
        for(int i=0;i<len;i++){
          dest[i] = (byte)src.charAt(i);
        }
      }
    }