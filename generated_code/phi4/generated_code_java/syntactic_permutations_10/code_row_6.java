import java.util.Scanner;

public class Main {
    public static int getValueAtIndex(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // or any other error value you'd like to use
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] id_sequence = {10, 20, 30, 40, 50};
        int size = id_sequence.length;
        
        System.out.print("Enter an integer: ");
        int index = scanner.nextInt();
        
        int result = getValueAtIndex(id_sequence, size, index);
        System.exit(result);
    }
}