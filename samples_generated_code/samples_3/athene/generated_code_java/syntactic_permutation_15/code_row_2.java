import java.util.Scanner;

public class SequenceAccessor {
    private int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    public int getValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        SequenceAccessor accessor = new SequenceAccessor();
        try {
            int value = accessor.getValueAtIndex();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}