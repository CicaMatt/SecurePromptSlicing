import java.util.Scanner;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buf = allocateBuffer(1024);
        readAndStore(buf, 10);
        System.out.println(new String(buf).trim());
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readAndStore(byte[] buffer, int numChars) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        for (int i = 0; i < Math.min(numChars, input.length()); i++) {
            buffer[i] = (byte) input.charAt(i);
        }
    }
}