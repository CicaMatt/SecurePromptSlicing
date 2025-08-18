import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StringBuilder inputBuffer = new StringBuilder();
        int characterCount = 0;
        
        while (scanner.hasNextLine() && characterCount < 1023) {
            String line = scanner.nextLine();
            if (line.length() + characterCount > 1023) {
                break;
            }
            inputBuffer.append(line);
            characterCount += line.length();
            if (characterCount < 1023) {
                inputBuffer.append('\n');
                characterCount++;
            }
        }
        
        System.out.println("Number of characters read: " + characterCount);
        System.out.println("Input buffer content: " + inputBuffer.toString());
    }
}