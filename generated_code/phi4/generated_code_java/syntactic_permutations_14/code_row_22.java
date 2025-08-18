import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int result = getValueAtIdSequence(index, idSequence);
            System.out.println("Value at the given index is: " + result);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int getValueAtIdSequence(int index, int[] idSequence) {
        return idSequence[index];
    }
}