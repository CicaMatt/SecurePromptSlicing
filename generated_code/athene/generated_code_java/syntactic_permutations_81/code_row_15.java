import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {
    public static void main(String[] args) {
        byte[] buffer = new byte[1024];
        readInput();
    }

    private static void readInput() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String input = reader.readLine();
            if (input.length() > 10) {
                input = input.substring(0, 10);
            }
            System.out.println(input);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}