import java.util.*;

public class MemoryChunk{
   public static void main(String args[]) {
      int[] a = new int[10];
      int[] b = new int[10];
      
      for(int i=0;i<10;i++) {
         a[i] = i+1;
      }
      
      System.arraycopy(a, 0, b, 0, 10);
  
      System.out.println("Contents of second array");
      for(int i=0;i<10;i++) {
         System.out.print(b[i]+" ");
      }
   }
}