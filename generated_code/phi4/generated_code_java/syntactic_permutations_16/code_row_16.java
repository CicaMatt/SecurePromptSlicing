import java.util.Scanner;

public class ArrayValueAtIndex {
    public static void main(String[] args) {
        int[] myArray = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer index: ");
        int inputIndex = scanner.nextInt();
        
        if (inputIndex >= 0 && inputIndex < myArray.length) {
            System.out.println("Value at index " + inputIndex + ": " + myArray[inputIndex]);
        } else {
            System.out.println("Invalid index. Please enter an integer between 0 and " + (myArray.length - 1) + ".");
        }
        
        scanner.close();
    }
}