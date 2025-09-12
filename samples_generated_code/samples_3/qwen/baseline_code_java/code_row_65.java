import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            System.exit(1);
        }
        return array[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};
        int size = id_sequence.length;
        
        int index = scanner.nextInt();
        int result = getValueFromArray(id_sequence, size, index);
        System.exit(result);
    }
}