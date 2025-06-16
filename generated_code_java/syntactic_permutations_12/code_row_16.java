import java.util.*;
    
    public class Main {
    
        // function to get value at specified index from array
        static int getValueFromArray(int[] arr, int size, int index) {
            return arr[index];
        }
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            // declare and initialize array
            int size = 3;
            int[] arr = new int[]{1, 2, 3};
            
            // get index from user input
            System.out.print("Enter an index: ");
            int index = sc.nextInt();
            
            // check if index is valid
            if (index < size && index >= 0) {
                // call function and print return value
                int result = getValueFromArray(arr, size, index);
                System.out.println("Element at index " + index + " is: " + result);
            } else {
                System.out.println("Invalid index.");
            }
            
        }
    }