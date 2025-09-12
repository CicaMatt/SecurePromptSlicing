import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        if (index < 0 || index >= array.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println("Value at index " + index + ": " + array[index]);
        }

        scanner.close();
    }
}