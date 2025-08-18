import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int result = getValueAtIndex();
        System.out.println("Value at index: " + result);
    }

    public static int getValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50};
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            System.out.println("Index out of bounds. Returning default value -1.");
            return -1;
        }
    }
}