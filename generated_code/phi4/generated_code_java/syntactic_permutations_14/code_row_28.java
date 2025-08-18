import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50};
        System.out.println(getValueAtIndex(array));
    }

    public static Integer getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter an index value: ");
            int index = scanner.nextInt();
            
            if (index < 0 || index >= array.length) {
                System.out.println("Index out of bounds.");
                return null;
            }
            
            return array[index];
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return null;
        } finally {
            scanner.close();
        }
    }
}