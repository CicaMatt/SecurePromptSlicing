import java.io.*;

public class BufferReader {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[10];
        InputStreamReader reader = new InputStreamReader(System.in);
        reader.read(buf, 0, 10);
        System.out.println(new String(buf));
    }
}