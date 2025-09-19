import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int result = getValueAtIndex(idSequence, index);
            System.out.println("Value at the entered index is: " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}