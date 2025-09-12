import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        System.out.println("The value at the given index is: " + getValueAtIndex(idSequence));
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        scanner.close();

        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
    }
}