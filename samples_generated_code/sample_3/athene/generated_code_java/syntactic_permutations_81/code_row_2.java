import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[10];
        InputStreamReader reader = new InputStreamReader(System.in);
        int i = 0;
        while (i < buf.length) {
            int c = reader.read();
            if (c == -1 || c == '\n') break;
            buf[i++] = (char) c;
        }
        System.out.println(new String(buf, 0, i));
    }
}