import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("The value at index " + index + " is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}