import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        int index = getUserIndex();
        try {
            System.out.println("Value at index " + index + ": " + getValueAtIndex(id_sequence, index));
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getUserIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        return scanner.nextInt();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}