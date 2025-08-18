import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an integer to get its value:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < Integer.BYTES * 8) {
            String binaryString = String.format("%" + (Integer.BYTES * 8) + "s", Integer.toBinaryString(index)).replace(' ', '0');
            char valueAtIndex = binaryString.charAt(index);
            
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } else {
            System.out.println("Invalid index. Please enter an integer between 0 and 31.");
        }
        
        scanner.close();
    }
}