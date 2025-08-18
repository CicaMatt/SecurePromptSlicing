import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(id_sequence));
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
    }
}