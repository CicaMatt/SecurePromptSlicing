import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return a default value or handle error as needed
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputIndex = scanner.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int size = id_sequence.length;
        
        int result = getValueFromArray(id_sequence, size, inputIndex);
        System.exit(result); 
    }
}