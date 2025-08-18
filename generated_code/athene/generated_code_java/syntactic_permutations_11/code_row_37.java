import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        return -1; // Return -1 for invalid index
    }

    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5};
        int size = id_sequence.length;
        
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        
        int result = getValueFromArray(id_sequence, size, index);
        System.out.println(result);
    }
}