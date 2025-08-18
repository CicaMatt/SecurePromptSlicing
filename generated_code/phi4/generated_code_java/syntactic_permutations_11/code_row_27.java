import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        System.out.print("Enter an integer: ");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, index);
        System.exit(result);
    }
}