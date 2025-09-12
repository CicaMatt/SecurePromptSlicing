import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // Return a default value or handle error as needed
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the elements of the array (space-separated):");
        String inputLine = scanner.nextLine();
        
        String[] stringValues = inputLine.trim().split("\\s+");
        int[] array = new int[stringValues.length];
        
        for (int i = 0; i < stringValues.length; i++) {
            array[i] = Integer.parseInt(stringValues[i]);
        }
        
        System.out.println("Enter the index:");
        int index = scanner.nextInt();
        
        int result = getValueFromArray(array, array.length, index);
        
        // Return result as the exit code
        System.exit(result);
    }
}