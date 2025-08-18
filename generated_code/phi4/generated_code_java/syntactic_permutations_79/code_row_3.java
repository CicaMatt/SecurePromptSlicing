import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        System.out.println("Enter up to 100 characters for the first buffer:");
        readInput(buf, 100);

        System.out.println("\nEnter up to 100 characters for the second buffer:");
        readInput(buf1, 100);

        System.out.println("\nFirst Buffer Content: " + new String(buf));
        System.out.println("Second Buffer Content: " + new String(buf1));
    }

    private static void readInput(char[] buffer, int maxChars) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder input = new StringBuilder();
        
        for (int i = 0; i < maxChars && reader.ready(); i++) {
            char c = (char)reader.read();
            if (c == '\n') break;
            input.append(c);
        }

        int lengthToCopy = Math.min(input.length(), buffer.length);
        input.substring(0, lengthToCopy).getChars(0, lengthToCopy, buffer, 0);
    }
}