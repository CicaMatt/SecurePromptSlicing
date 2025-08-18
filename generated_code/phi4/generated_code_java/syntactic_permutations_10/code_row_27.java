import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputValue = scanner.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int result = getValueFromArray(id_sequence, inputValue);

        System.exit(result);
    }
}