import java.util.Scanner;

public class ArrayIndexer {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        try {
            System.out.println(getValueAtIndex(idSequence));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static String getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index < 0 || index >= idSequence.length) {
            return "Index out of bounds.";
        }
        
        return String.valueOf(idSequence[index]);
    }
}