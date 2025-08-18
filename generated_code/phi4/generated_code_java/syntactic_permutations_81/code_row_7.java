import java.io.IOException;
import java.util.Arrays;

public class MemoryAllocation {

    private static final int SIZE = 1024;
    private byte[] buffer;

    public MemoryAllocation() {
        allocateMemory();
    }

    private void allocateMemory() {
        buffer = new byte[SIZE];
    }

    public String readFromStandardInput() throws IOException {
        char[] buf = new char[10];
        try (java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(System.in))) {
            int numCharsRead = 0;
            while (numCharsRead < 10) {
                String line = reader.readLine();
                if (line == null) break; // EOF or error
                for (int i = 0; i < line.length() && numCharsRead < 10; i++, numCharsRead++) {
                    buf[numCharsRead] = line.charAt(i);
                }
            }
        }
        return new String(buf, 0, Math.min(10, buf.length));
    }

    public static void main(String[] args) throws IOException {
        MemoryAllocation memoryAllocation = new MemoryAllocation();
        System.out.println("Enter up to 10 characters:");
        String result = memoryAllocation.readFromStandardInput();
        System.out.println("You entered: " + result);
    }
}