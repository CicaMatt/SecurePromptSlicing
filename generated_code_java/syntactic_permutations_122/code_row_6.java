// Java program to demonstrate memory allocation using malloc() and free().
      
    import java.util.*;
    class GFG {
        public static void main(String[] args) {
            int size = 10;
            byte[] array = new byte[size];
          
            // Copying array to another
            for (int i = 0; i < size; i++) {
                System.out.println("Allocating memory dynamically " +
                    "for second array");
                byte[] arr = new byte[size];
                
                // Copying array to another array
                for (int j = 0; j < size; j++) {
                    arr[j] = array[j];
                    System.out.println("Value at index " + j + " is : " +
                            arr[j]);
                }
          
                // Freeing first array
                System.gc();
                System.out.println("\nFreeing memory of first array");
          
                // Freeing second array
                System.gc();
                System.out.println("Freeing memory of second array");
            }
        }
    }