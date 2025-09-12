import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        int index = promptForIndex();
        try {
            System.out.println("The value at index " + index + " is: " + getValueAtIndex(idSequence, index));
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    private static int promptForIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        return Integer.parseInt(scanner.nextLine());
    }

    private static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}