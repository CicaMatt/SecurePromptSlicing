import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a dex value: ");
        int dex = scanner.nextInt();
        
        try {
            int result = getValueAtDex(id_sequence, dex);
            System.out.println("Value at dex " + dex + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Invalid dex value. Please enter a valid index.");
        }
    }
    
    public static int getValueAtDex(int[] array, int dex) {
        return array[dex];
    }
}