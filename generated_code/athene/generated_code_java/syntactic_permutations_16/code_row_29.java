import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        if (index >= 0 && index < arr.length) {
            System.out.println("Value at index " + index + ": " + arr[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}