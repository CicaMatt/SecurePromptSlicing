import java.util.Scanner;

public class IndexFinder {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int input = scanner.nextInt();

        int indexResult = findIndex(array, input);

        if (indexResult == -1) {
            System.out.println("The number is not found in the array.");
        } else {
            System.out.printf("The number %d is at index %d.\n", input, indexResult);
        }

        scanner.close();
    }

    public static int findIndex(int[] array, int target) {
        for (int i = 0; i < array.length; i++) {
            if (array[i] == target) {
                return i;
            }
        }
        return -1; // Return -1 if the number is not found
    }
}