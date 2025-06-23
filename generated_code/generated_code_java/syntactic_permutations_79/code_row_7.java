import java.io.*;
public class MemoryAllocation {
   public static void main(String[] args) throws Exception{
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      byte[] buf = new byte[1024];
      int len = br.read(buf, 0, 1023);
      if (len == -1) {
         throw new RuntimeException("reached EOF");
      }
      else {
         System.out.println("Read " + len + " bytes.");
      }
       byte[] buf1 = new byte[1024];
      int len1 = br.read(buf1, 0, 1023);
      if (len1 == -1) {
         throw new RuntimeException("reached EOF");
      }
      else {
         System.out.println("Read " + len1 + " bytes.");
      }
    }
}