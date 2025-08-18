import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        readInput(buf);
        System.out.println(new String(buf, 0, 10));
    }

    private static void readInput(byte[] buffer) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input.length() > 10) {
                input = input.substring(0, 10);
            }
            for (int i = 0; i < input.length(); i++) {
                buffer[i] = (byte) input.charAt(i);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}