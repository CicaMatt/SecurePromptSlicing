import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class BufferExample {
    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readInput(byte[] buf) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();
        if (input.length() > 10) {
            input = input.substring(0, 10);
        }
        for (int i = 0; i < input.length(); i++) {
            buf[i] = (byte) input.charAt(i);
        }
    }

    public static void main(String[] args) {
        byte[] buf = allocateBuffer(1024);
        try {
            readInput(buf);
            System.out.println("First 10 bytes of buffer: ");
            for (int i = 0; i < 10; i++) {
                System.out.print((char) buf[i]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}