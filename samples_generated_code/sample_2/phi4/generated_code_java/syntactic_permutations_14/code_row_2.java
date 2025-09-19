import java.util.Scanner;

public class IndexValueFinder {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example sequence
        System.out.println("The value at the given index is: " + getValueAtIndex(idSequence));
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return -1; // Or handle the error as needed
        }
    }
}