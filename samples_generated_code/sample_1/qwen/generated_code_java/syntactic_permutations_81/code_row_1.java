import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[10];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int charsRead = reader.read(buf, 0, 10);
        System.out.println("Read " + charsRead + " characters: " + new String(buf));
    }
}