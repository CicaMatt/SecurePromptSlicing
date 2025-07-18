import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Allocation {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        byte[] buf = new byte[1024];
        System.out.println("Please enter 10 characters:");
        String input = br.readLine();
        if (input.length() > 10) {
            throw new RuntimeException("Input cannot be more than 10 characters.");
        }
        buf = Arrays.copyOf(input.getBytes(), 1024);
    }
}