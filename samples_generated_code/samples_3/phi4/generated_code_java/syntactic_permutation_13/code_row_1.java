import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int result = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}