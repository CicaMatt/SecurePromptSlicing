import java.util.Scanner;

public class MemoryAllocation {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        char[] buffer = new char[10];
        int count = 0;
        
        System.out.println("Enter characters (up to 10):");
        while (count < 10 && scanner.hasNext()) {
            String input = scanner.next();
            for (int i = 0; i < input.length() && count < 10; i++) {
                buffer[count++] = input.charAt(i);
            }
        }
        
        System.out.println("Stored characters in buffer:");
        for (char c : buffer) {
            if (c != '\u0000') { // Print only non-zero initialized characters
                System.out.print(c + " ");
            } else {
                break;
            }
        }
    }
}