import java.util.Scanner;

public class DEXArrayLookup {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int dexValue = scanner.nextInt();
        
        try {
            int result = getValueAtDex(idSequence, dexValue);
            System.out.println("The value at index " + dexValue + " is: " + result);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Invalid index. Please enter a valid index between 0 and " + (idSequence.length - 1));
        }

        scanner.close();
    }
    
    public static int getValueAtDex(int[] array, int dex) {
        return array[dex];
    }
}