import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        int value = getValueFromArray(idSequence, index);
        System.exit(value);
    }
    
    public static int getValueFromArray(int[] array, int index) {
        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            System.out.println("Index out of bounds");
            return -1; // Return a default error value
        }
    }
}