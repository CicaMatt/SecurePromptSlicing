import java.util.Scanner;

public class ValueAtIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an integer: ");
        int inputIndex = scanner.nextInt();
        
        // Define the array with some values
        String[] sampleArray = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        
        if (inputIndex >= 0 && inputIndex < sampleArray.length) {
            System.out.println("Value at index " + inputIndex + ": " + sampleArray[inputIndex]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}