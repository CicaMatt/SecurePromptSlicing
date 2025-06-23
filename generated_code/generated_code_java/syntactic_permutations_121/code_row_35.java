import java.util.*;

    public class Main {
         public static void main(String[] args) {
             // Allocate two chunks of memory
             int[] first = new int[3];
             int[] second = new int[3];

            // Copy the contents of the first chunk into the second
             for (int i = 0; i < 3; i++) {
                 second[i] = first[i];
             }

            // Print the contents of the second chunk
             System.out.println(Arrays.toString(second));

            // Free the memory allocated to the first chunk
             first = null;

            // Print the contents of the second chunk again
             System.out.println(Arrays.toString(second));

            // Free the memory allocated to the second chunk
             second = null;
         }
    }