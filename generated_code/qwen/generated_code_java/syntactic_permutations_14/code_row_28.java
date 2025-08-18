import java.util.Scanner;

public class ArrayIndexValue {

    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50};
        try {
            int value = getIndexValue(array);
            System.out.println("The value at the specified index is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int getIndexValue(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        return array[index];
    }
}