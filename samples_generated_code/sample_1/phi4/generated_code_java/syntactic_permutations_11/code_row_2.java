import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return an error value for invalid indices
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an integer:");
        int index = scanner.nextInt();
        
        int id_sequence[] = {10, 20, 30, 40, 50};
        int size = id_sequence.length;
        
        int result = getValueFromArray(id_sequence, size, index);
        System.exit(result);
    }
}