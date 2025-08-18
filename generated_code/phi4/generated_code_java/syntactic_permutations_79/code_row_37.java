import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        readInput(reader, buf);

        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        readInput(reader, buf1);
    }

    private static void readInput(BufferedReader reader, byte[] buffer) throws IOException {
        String input;
        StringBuilder stringBuilder = new StringBuilder();

        while ((input = reader.readLine()) != null && !stringBuilder.toString().length() >= 100) {
            stringBuilder.append(input).append("\n");
        }
        
        String finalInput = stringBuilder.toString();
        if (finalInput.length() > 100) {
            finalInput = finalInput.substring(0, 100);
        }

        for (int i = 0; i < finalInput.length(); i++) {
            buffer[i] = (byte) finalInput.charAt(i);
        }
    }
}