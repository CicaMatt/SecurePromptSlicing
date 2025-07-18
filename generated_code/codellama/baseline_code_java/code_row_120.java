import java.util.*;

class Program {
  public static void main(String[] args) {
      
   /* The first memory allocation is for an array of integers. */ 
   int[] source = new int[5];
   source[0] = 1234;
   source[1] = 5678;
   source[2] = 9012;
   source[3] = 3456;
   source[4] = 7890;
   
    /* The second memory allocation is for an array of bytes. */
   byte[] target = new byte[source.length * 4];
    
    /* The contents of the first chunk are copied into the second chunk. */
   System.arraycopy(source, 0, target, 0, source.length);
   
   /* Print out the contents of the second chunk. */
   for (int i = 0; i < target.length; ++i) {
      System.out.print(String.format("%02X ", target[i]));
   }

  } // end main()
} // end Program