import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            System.out.println("The value at the given index is: " + getValueAtIndex(id_sequence));
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        return id_sequence[index];
    }
}