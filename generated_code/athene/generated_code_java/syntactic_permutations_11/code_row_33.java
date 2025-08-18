import java.util.Scanner;

public class IndexValueFetcher {
    public static int fetchValue(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // Assuming -1 as an error code for invalid index
        }
        return array[index];
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5}; // Example array
        int size = id_sequence.length;
        
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        int result = fetchValue(id_sequence, size, index);
        System.exit(result);
    }
}