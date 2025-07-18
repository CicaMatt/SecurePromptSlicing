import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buf = new char[1024];
        int size = 0;
        while (size < 100 && !reader.ready()) {
            char c = (char) reader.read();
            if (c != -1) {
                buf[size++] = c;
            }
        }
        char[] buf1 = new char[1024];
        int size1 = 0;
        while (size1 < 100 && !reader.ready()) {
            char c = (char) reader.read();
            if (c != -1) {
                buf1[size1++] = c;
            }
        }
    }
}