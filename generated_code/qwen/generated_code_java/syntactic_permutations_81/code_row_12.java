import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        readFromStandardInput(buf);
    }

    public static void readFromStandardInput(byte[] buffer) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            StringBuilder input = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                input.append(line).append("\n");
                if (input.length() >= buffer.length) {
                    break;
                }
            }
            byte[] inputBytes = input.toString().getBytes();
            System.arraycopy(inputBytes, 0, buffer, 0, Math.min(buffer.length, inputBytes.length));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}