import java.io.IOException;
import java.io.InputStream;

public class BufferExample {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        byte[] buffer = new byte[BUFFER_SIZE];
        InputStream inputStream = System.in;

        try {
            int bytesRead = inputStream.read(buffer, 0, 10);
            if (bytesRead != -1) {
                String input = new String(buffer, 0, bytesRead);
                System.out.println("Read: " + input);
            } else {
                System.out.println("No input available.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}