import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 or any other error code for invalid index
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int idSequence[] = {10, 20, 30, 40, 50}; // Example array

        System.out.print("Enter an integer: ");
        int inputIndex = scanner.nextInt();
        
        int result = getValueFromArray(idSequence, idSequence.length, inputIndex);

        System.exit(result);
    }
}