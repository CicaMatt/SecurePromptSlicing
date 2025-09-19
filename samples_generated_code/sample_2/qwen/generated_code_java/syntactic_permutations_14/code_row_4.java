import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            int result = getValueAtIndex(id_sequence);
            System.out.println("The value at the given index is: " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: The provided index is out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}