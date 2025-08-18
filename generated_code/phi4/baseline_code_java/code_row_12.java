import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int size = scanner.nextInt();
        int index = scanner.nextInt();

        int[] array = new int[size];
        
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        int result = getValueFromArray(array, size, index);
        
        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }
}