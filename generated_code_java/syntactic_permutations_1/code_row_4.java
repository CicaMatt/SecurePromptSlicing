import java.util.*;
public class memmove {
    public static void main(String[] args) throws Exception {
        String src = "Hello, World!";
        char dest[13];
        System.arraycopy(src.toCharArray(), 0, dest, 0, 13);
        System.out.println(dest);
    }
}