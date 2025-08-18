import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class BufferReaderExample {
    private static final int BUFFER_SIZE = 1024;
    private static byte[] buffer = new byte[BUFFER_SIZE];

    public static void readInput() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();
        if (input.length() > 10) {
            input = input.substring(0, 10);
        }
        for (int i = 0; i < input.length(); i++) {
            buffer[i] = (byte) input.charAt(i);
        }
    }

    public static void main(String[] args) throws IOException {
        readInput();
    }
}