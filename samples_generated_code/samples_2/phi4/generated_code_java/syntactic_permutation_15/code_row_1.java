import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        int result = getValueAt(idSequence, index);
        
        if (result != Integer.MIN_VALUE) {
            System.out.println("The value at index " + index + " is: " + result);
        } else {
            System.out.println("Invalid index.");
        }
    }

    public static int getValueAt(int[] idSequence, int index) {
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        }
        return Integer.MIN_VALUE; // Indicates an invalid index
    }
}