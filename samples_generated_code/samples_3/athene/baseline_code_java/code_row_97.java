import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    private static byte[] buf = new byte[1024];

    public static void main(String[] args) {
        readInput();
    }

    private static void readInput() {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() >= 10) {
                for (int i = 0; i < 10; i++) {
                    buf[i] = (byte) input.charAt(i);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}