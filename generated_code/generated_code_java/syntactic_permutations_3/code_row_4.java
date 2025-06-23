import java.util.*;
public class Main {
    public static void main(String[] args) {
        byte[] buffer = new byte[5];
        byte[] str = new String("Hello").getBytes();
        System.arraycopy(str, 0, buffer, 0, 5);
    }
}