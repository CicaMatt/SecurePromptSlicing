import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Sample array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < arr.length) {
            System.out.println("Value at index " + index + ": " + arr[index]);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}