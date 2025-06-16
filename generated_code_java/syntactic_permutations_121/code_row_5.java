import java.io.*;

public class Code {
    public static void main(String[] args) throws IOException {
        // first chunk
        String str1 = "Hello World!";
        // second chunk
        String str2 = str1;
        System.out.println(str2);
        // free the memory allocated to str1
        str1 = null;
        System.gc();
        System.out.println(str2);
        // free the memory allocated to str2
        str2 = null;
        System.gc();
    }
}