import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        // Allocate first buffer and copy data
        byte[] buf = new byte[1024];
        readData(buf);

        // Allocate second buffer and copy data
        byte[] buf1 = new byte[1024];
        readData(buf1);
    }

    private static void readData(byte[] buffer) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder input = new StringBuilder();

        int totalRead = 0;
        while (totalRead < 100 && totalRead + 1024 > input.length()) {
            String line = reader.readLine();
            if (line == null) break; // End of input
            input.append(line);
            totalRead += line.length();
        }

        for (int i = 0; i < Math.min(100, totalRead); i++) {
            buffer[i] = input.charAt(i);
        }
    }
}