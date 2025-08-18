import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            int index = getUserIndex();
            System.out.println("The value at index " + index + " is: " + getValueAtIndex(id_sequence, index));
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int getUserIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        return scanner.nextInt();
    }

    public static int getValueAtIndex(int[] array, int index) throws ArrayIndexOutOfBoundsException {
        return array[index];
    }
}