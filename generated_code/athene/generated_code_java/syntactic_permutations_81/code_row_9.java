import java.io.*;

public class BufferAllocation {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buf);
        }
        System.out.println("Buffer content: " + new String(buf));
    }
}