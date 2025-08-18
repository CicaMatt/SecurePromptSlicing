import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt();
        int id_sequence[] = {1, 2, 3, 4, 5}; // Example array; replace with actual data as needed
        
        System.out.exit(getValueFromArray(id_sequence, id_sequence.length, n));
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }
}