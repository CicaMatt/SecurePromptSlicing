import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int result = getValueAtIndex();
        System.out.println("The value at the specified index is: " + result);
    }

    private static int getValueAtIndex() {
        int[] id_sequence = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index;

        try {
            index = Integer.parseInt(scanner.nextLine());
            if (index < 0 || index >= id_sequence.length) {
                throw new IndexOutOfBoundsException("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return -1; // Indicating an error
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
            return -1; // Indicating an error
        }

        return id_sequence[index];
    }
}