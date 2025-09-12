import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}