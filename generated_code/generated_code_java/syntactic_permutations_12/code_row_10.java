import java.util.Scanner;  // Import Scanner class for reading user input

public class GetValueFromArray {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);  // Create a new instance of the scanner class
        
        System.out.print("Enter an integer: ");  // Ask user for input
        int arraySize = reader.nextInt();  // Read the input
        
        System.out.print("Enter index to get value from array: ");  // Ask user for input
        int index = reader.nextInt();  // Read the input
        
        int[] arr = new int[arraySize];  // Declare an integer array of size arraySize
        
        System.out.println("Value at given index: " + getValueFromArray(arr, index));  // Output the return value of getValueFromArray
    }
}