import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {1, 2, 3, 4, 5}; // Example array, can be modified or generated dynamically

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int index = scanner.nextInt();

        int value = getValueFromArray(idSequence, idSequence.length, index);

        System.exit(value);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            return -1; // Return a default value or handle the error as needed
        }
    }
}