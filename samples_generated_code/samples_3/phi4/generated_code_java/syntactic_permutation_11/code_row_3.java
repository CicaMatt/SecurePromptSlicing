import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int inputIndex = scanner.nextInt();
        int result = getValueFromArray(new int[]{1, 2, 3, 4, 5}, 5, inputIndex);

        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1;
    }
}