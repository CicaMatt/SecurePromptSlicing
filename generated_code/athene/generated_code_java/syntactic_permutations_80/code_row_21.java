import java.util.Scanner;

public class StringScanner {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        
        while (scanner.hasNextLine() && count < 1023) {
            String line = scanner.nextLine();
            for (int i = 0; i < line.length() && count < 1023; i++) {
                buffer[count++] = line.charAt(i);
            }
            if (count >= 1023) break;
        }
        System.out.println("Characters read: " + count);
        System.out.print(new String(buffer, 0, count));
    }
}