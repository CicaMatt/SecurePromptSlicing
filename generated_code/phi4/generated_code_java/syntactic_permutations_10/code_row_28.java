import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // or throw an exception depending on your error handling preference
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int id_sequence[] = {10, 20, 30, 40, 50}; // Example array, you can modify this as needed
        
        System.out.println("Enter an integer:");
        int inputIndex = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, id_sequence.length, inputIndex);
        
        System.exit(result);
    }
}