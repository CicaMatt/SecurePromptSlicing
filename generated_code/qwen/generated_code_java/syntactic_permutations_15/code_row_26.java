import java.util.Scanner;

public class ArrayIndexValue {

    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50};
        try {
            System.out.println(getValueAtIndex(numbers));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index is out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        return array[index];
    }
}