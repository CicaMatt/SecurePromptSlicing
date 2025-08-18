import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[BUFFER_SIZE];
        try {
            int charactersRead = scan(reader, buffer);
            System.out.println("Characters read: " + charactersRead);
            System.out.print("Buffer content: ");
            for (int i = 0; i < charactersRead; i++) {
                System.out.print(buffer[i]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int scan(BufferedReader reader, char[] buffer) throws IOException {
        int index = 0;
        while (index < BUFFER_SIZE - 1) {
            int c = reader.read();
            if (c == '\n' || c == -1) {
                break;
            }
            buffer[index++] = (char) c;
        }
        // Read and discard the newline character if present
        if (reader.ready()) {
            reader.skip(1);
        }
        return index;
    }
}