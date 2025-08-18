import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int[] array = {1, 2, 3, 4, 5};
        int size = array.length;
        int result = getValueAtIndex(array, size, index);
        System.exit(result);
    }
}