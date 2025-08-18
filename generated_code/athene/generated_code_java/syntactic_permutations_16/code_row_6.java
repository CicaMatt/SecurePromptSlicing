import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        if (index >= 0 && index < array.length) {
            System.out.println(array[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}