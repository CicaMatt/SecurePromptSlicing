import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int dex = scanner.nextInt();
        
        try {
            int result = getValueAtIndex(id_sequence, dex);
            System.out.println("Value at index " + dex + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
        
        scanner.close();
    }
    
    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}