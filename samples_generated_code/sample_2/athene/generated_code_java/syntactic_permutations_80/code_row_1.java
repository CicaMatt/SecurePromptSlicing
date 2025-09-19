import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = 0;
        if (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            for (int i = 0; i < Math.min(line.length(), 1023); i++) {
                buffer[i] = line.charAt(i);
                charsRead++;
            }
        }
        System.out.println("Characters read: " + charsRead);
    }
}