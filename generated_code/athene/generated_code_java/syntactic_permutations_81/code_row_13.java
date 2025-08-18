import java.util.Scanner;

public class BufferExample {
    private static byte[] buf = new byte[1024];

    public static void main(String[] args) {
        readAndStore();
    }

    private static void readAndStore() {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        if (input.length() > 10) {
            input = input.substring(0, 10);
        }
        for (int i = 0; i < input.length(); i++) {
            buf[i] = (byte) input.charAt(i);
        }
    }
}