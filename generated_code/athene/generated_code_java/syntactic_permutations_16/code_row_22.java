import java.util.Scanner;

public class ArrayIndexFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        System.out.print("Enter an integer: ");
        int input = scanner.nextInt();
        
        if (input >= 0 && input < array.length) {
            System.out.println("Value at index " + input + ": " + array[input]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}