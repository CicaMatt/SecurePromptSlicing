import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an integer:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(idSequence, idSequence.length, index);

        // Use the result as the exit code
        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            return -1; // Return -1 or any default/error value for invalid indices
        }
    }
}