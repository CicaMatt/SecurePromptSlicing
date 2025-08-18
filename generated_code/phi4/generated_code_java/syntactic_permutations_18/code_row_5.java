import java.util.Scanner;

public class ArrayElementFinder {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example array

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < array.length) {
            System.out.println("The value at index " + index + " is " + array[index]);
        } else {
            System.out.println("Index out of bounds");
        }
        
        scanner.close();
    }
}