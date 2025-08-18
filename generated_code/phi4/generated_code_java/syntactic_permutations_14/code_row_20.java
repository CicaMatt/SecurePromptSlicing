import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println("Value at entered index: " + getValueAtUserIndex(id_sequence));
    }

    public static int getValueAtUserIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.print("Enter an index value: ");
            int index = scanner.nextInt();
            
            if (index < 0 || index >= array.length) {
                throw new IndexOutOfBoundsException("Index out of bounds");
            }
            
            return array[index];
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return -1; // Indicating an error
        } finally {
            scanner.close();
        }
    }
}