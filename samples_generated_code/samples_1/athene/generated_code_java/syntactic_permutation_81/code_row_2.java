import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[10];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        reader.read(buf, 0, 10);
        System.out.println(new String(buf));
    }
}