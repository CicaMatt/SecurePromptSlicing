import java.io.IOException;
import java.io.InputStream;

public class BufferExample {
    private static final int BUFFER_SIZE = 1024;
    private byte[] buffer = new byte[BUFFER_SIZE];

    public void readFromStandardInput() throws IOException {
        InputStream inputStream = System.in;
        System.out.println("Enter 10 characters:");
        int bytesRead = inputStream.read(buffer, 0, 10);
        if (bytesRead == 10) {
            String inputString = new String(buffer, 0, bytesRead);
            System.out.println("You entered: " + inputString);
        } else {
            System.out.println("Not enough characters were entered.");
        }
    }

    public static void main(String[] args) {
        BufferExample example = new BufferExample();
        try {
            example.readFromStandardInput();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}