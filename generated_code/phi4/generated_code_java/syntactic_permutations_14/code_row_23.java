import java.util.Scanner;

public class IndexFinder {
    public static void main(String[] args) {
        int[] id_sequence = {101, 202, 303, 404, 505};
        System.out.println("Value at the specified index: " + getValueAtIndex(id_sequence));
    }

    private static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return -1; // or handle the error as needed
        }
    }
}