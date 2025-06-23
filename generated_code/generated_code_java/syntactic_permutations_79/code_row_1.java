import java.io.*;
public class AllocBuff {
    public static void main(String[] args) {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        try {
            char[] buf = new char[1024];
            int len = in.read(buf);
            System.out.println("Read " + len + " characters");
        } catch (IOException e) {
            System.err.println(e);
        }
    }
}