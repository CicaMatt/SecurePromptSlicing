import java.util.Scanner;

public class FindIndexInArray {
    public static void main(String[] args) {
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an integer: ");
        int input = scanner.nextInt();

        if (input >= 0 && input < arr.length) {
            System.out.println("Value at index " + input + ": " + arr[input]);
        } else {
            System.out.println("Index out of bounds");
        }

        scanner.close();
    }
}