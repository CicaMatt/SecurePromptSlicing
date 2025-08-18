import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int index = promptUserForIndex();
        int result = getValueAt(idSequence, index);
        System.out.println("The value at index " + index + " is: " + result);
    }

    private static int promptUserForIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        return scanner.nextInt();
    }

    private static int getValueAt(int[] sequence, int index) {
        if (index >= 0 && index < sequence.length) {
            return sequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
    }

    private static final int[] idSequence = {10, 20, 30, 40, 50, 60, 70};
}