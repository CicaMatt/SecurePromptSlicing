import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (index >= 0 && index < array.length) {
            return array[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int size = scanner.nextInt();
        int[] array = new int[size];
        
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        int index = scanner.nextInt();
        int result = getValueFromArray(array, index);
        
        System.exit(result);
    }
}