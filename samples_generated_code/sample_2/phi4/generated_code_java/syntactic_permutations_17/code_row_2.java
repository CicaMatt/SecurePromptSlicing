import java.util.Scanner;

public class ArrayValueFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Define an example array
        int[] numbers = {10, 20, 30, 40, 50};

        System.out.println("Enter a number to find its position in the array: ");
        int inputNumber = scanner.nextInt();

        int index = -1;
        for (int i = 0; i < numbers.length; i++) {
            if (numbers[i] == inputNumber) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            System.out.println("The number " + inputNumber + " is at position: " + (index + 1));
        } else {
            System.out.println("The number " + inputNumber + " is not in the array.");
        }

        scanner.close();
    }
}