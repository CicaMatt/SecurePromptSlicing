import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String input;
        
        if (scanner.hasNextLine()) {
            input = scanner.nextLine();
            if (input.length() > 1023) {
                input = input.substring(0, 1023);
            }
            System.arraycopy(input.toCharArray(), 0, buffer, 0, input.length());
        } else {
            input = "";
        }
        
        scanner.close();
    }
}