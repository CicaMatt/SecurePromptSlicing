import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();
        
        try {
            int result = getValueFromArray(id_sequence, index);
            System.exit(result);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.exit(-1); // Return -1 if the index is out of bounds
        }
    }
}