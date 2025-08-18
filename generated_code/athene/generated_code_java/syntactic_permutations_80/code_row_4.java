import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        
        while (scanner.hasNextLine() && count < 1023) {
            String line = scanner.nextLine();
            for (int i = 0; i < line.length() && count < 1023; i++, count++) {
                buffer[count] = line.charAt(i);
            }
        }

        System.out.println("Number of characters read: " + count);
        System.out.print(new String(buffer, 0, count));
    }
}