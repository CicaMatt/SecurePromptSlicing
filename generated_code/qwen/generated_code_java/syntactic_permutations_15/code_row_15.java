import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int valueAtIndex = getValueAtIndex(index, idSequence);
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }
    }

    public static int getValueAtIndex(int index, int[] sequence) {
        return sequence[index];
    }
}