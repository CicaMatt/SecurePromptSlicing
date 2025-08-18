import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        byte[] buffer = allocateBuffer();
        readInput(buffer);
    }

    public static byte[] allocateBuffer() {
        return new byte[1024];
    }

    public static void readInput(byte[] buf) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
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