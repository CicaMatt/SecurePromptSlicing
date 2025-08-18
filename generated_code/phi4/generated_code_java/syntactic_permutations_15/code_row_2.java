import java.util.Scanner;

public class ArrayIndexFetcher {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        try {
            System.out.println("Value at index: " + getValueAtIndex(idSequence));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        try {
            int index = Integer.parseInt(scanner.nextLine());
            if (index < 0 || index >= idSequence.length) {
                throw new IndexOutOfBoundsException("Index is out of bounds.");
            }
            return idSequence[index];
        } finally {
            scanner.close();
        }
    }
}