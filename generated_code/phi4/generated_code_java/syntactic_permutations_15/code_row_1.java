import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        System.out.println("Please enter an index value:");
        Scanner scanner = new Scanner(System.in);
        try {
            int index = scanner.nextInt();
            if (index >= 0 && index < idSequence.length) {
                System.out.println("The value at the given index is: " + getValueAtIndex(idSequence, index));
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        } finally {
            scanner.close();
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}