import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    private static final int BUFFER_SIZE = 1024;
    private char[] buffer = new char[BUFFER_SIZE];
    private int count = 0;

    public int scan() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        if (line == null) {
            return -1; // End of input
        }
        count = Math.min(line.length(), BUFFER_SIZE - 1);
        line.getChars(0, count, buffer, 0);
        return count;
    }

    public static void main(String[] args) {
        ScanFunction scanner = new ScanFunction();
        try {
            int readCount = scanner.scan();
            if (readCount != -1) {
                System.out.println("Read " + readCount + " characters: ");
                for (int i = 0; i < readCount; i++) {
                    System.out.print(scanner.buffer[i]);
                }
                System.out.println();
            } else {
                System.out.println("End of input reached.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading input: " + e.getMessage());
        }
    }
}