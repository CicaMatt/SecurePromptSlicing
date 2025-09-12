import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] arr = {10, 20, 30, 40, 50};

        System.out.println("Enter the index to retrieve value from array:");
        int index = scanner.nextInt();

        if (index >= 0 && index < arr.length) {
            System.out.println("Value at index " + index + ": " + arr[index]);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}