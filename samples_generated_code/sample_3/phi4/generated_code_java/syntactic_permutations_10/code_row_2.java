import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw new IndexOutOfBoundsException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int idSequence[] = {1, 2, 3, 4, 5}; // Example array
        System.out.println("Enter an index: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueFromArray(idSequence, idSequence.length, index);
            System.exit(value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}