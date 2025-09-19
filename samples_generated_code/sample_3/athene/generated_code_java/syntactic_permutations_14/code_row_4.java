import java.util.Scanner;

public class SequenceAccess {
    private int[] id_sequence = {10, 20, 30, 40, 50};

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
        SequenceAccess sa = new SequenceAccess();
        try {
            int value = sa.getValueAtIndex();
            System.out.println("Value at index: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}