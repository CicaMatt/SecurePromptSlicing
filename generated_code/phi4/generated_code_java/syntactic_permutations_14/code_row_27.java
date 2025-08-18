import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array; modify as needed.
        
        try {
            System.out.println("Enter an index value: ");
            Scanner scanner = new Scanner(System.in);
            int index = scanner.nextInt();
            
            if (index < 0 || index >= idSequence.length) {
                throw new IndexOutOfBoundsException("Index is out of bounds");
            }

            int valueAtGivenIndex = getValueAtIndex(idSequence, index);
            System.out.println("Value at the given index: " + valueAtGivenIndex);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] idSequence, int index) {
        return idSequence[index];
    }
}