import java.util.Scanner;

public class IdSequence {

    public static void main(String[] args) {
        int[] id_sequence = {101, 102, 103, 104, 105};
        
        try {
            System.out.println(getValueAtIndex(id_sequence));
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        try {
            int index = Integer.parseInt(scanner.nextLine());

            if (index < 0 || index >= array.length) {
                throw new IndexOutOfBoundsException("Index is out of bounds.");
            }

            return array[index];
        } finally {
            scanner.close();
        }
    }
}