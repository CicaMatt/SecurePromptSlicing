import java.util.Scanner;

public class Main {

    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the size of the array:");
        int size = scanner.nextInt();
        
        int[] id_sequence = new int[size];
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < size; i++) {
            id_sequence[i] = scanner.nextInt();
        }
        
        System.out.println("Enter the index to retrieve:");
        int index = scanner.nextInt();
        
        try {
            int result = getValueFromArray(id_sequence, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}