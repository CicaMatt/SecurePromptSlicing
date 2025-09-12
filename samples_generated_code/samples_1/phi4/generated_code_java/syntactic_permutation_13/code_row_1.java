import java.util.Scanner;

public class ArrayValueRetriever {

    public static int getValueAtIndex(int index) {
        int[] idSequence = {10, 20, 30, 40, 50, 60};
        
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index value: ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            int value = getValueAtIndex(index);
            System.out.println("Value at the given index: " + value);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}