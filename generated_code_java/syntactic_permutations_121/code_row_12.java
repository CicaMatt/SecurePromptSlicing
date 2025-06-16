import java.util.Arrays;
public class MemoryManipulation {
   public static void main(String[] args){
       // Allocate two chunks of memory
       byte[] arr1 = new byte[32];
       byte[] arr2 = new byte[64];
       
       // Fill the first array with data
       for (int i = 0;i < arr1.length;i++) {
           arr1[i] = (byte) i;
       }
       
       // Copy the first array to second array
       System.arraycopy(arr1, 0, arr2, 0, arr1.length);
       
       // Print out the contents of the second array
       System.out.println("Second Array Contents");
       for (int i = 0;i < arr2.length;i++) {
           System.out.print(arr2[i] + " ");
       }
       
       // Free first chunk of memory
       arr1 = null;
       System.gc();
       
       // Print out the contents of the second array after garbage collection
       System.out.println("\n\nSecond Array Contents After Garbage Collection");
       for (int i = 0;i < arr2.length;i++) {
           System.out.print(arr2[i] + " ");
       }
       
       // Free second chunk of memory
       arr2 = null;
       System.gc();
   }
}