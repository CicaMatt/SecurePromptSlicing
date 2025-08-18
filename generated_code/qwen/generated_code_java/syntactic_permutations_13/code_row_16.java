import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index value:");
        int index = scanner.nextInt();
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + " is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int index) {
        int[] array = {10, 20, 30, 40, 50};
        return array[index];
    }
}