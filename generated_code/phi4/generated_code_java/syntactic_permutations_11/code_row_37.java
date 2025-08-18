import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
    }

    public static void main(String[] args) {
        int id_sequence[] = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer for the index: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueFromArray(id_sequence, id_sequence.length, index);
            System.out.println(value);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }

        scanner.close();
    }
}