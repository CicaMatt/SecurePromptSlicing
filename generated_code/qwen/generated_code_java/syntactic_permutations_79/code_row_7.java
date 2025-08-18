import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        char[] buf = new char[1024];
        reader.read(buf, 0, 100);

        char[] buf1 = new char[1024];
        reader.read(buf1, 0, 100);
    }
}