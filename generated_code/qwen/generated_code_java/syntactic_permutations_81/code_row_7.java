import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] memory = allocateMemory(1024);
        char[] buf = new char[10];
        readInput(buf);

        // For demonstration, print the characters read
        System.out.println("Read characters: " + new String(buf));
    }

    public static byte[] allocateMemory(int size) {
        return new byte[size];
    }

    public static void readInput(char[] buffer) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buffer, 0, 10);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}