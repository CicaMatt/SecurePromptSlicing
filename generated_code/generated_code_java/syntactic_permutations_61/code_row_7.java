import java.util.*;
public class Main {
    public static void main(String[] args) {
        int buffer_size = 1024;
        byte[] buffer = new byte[buffer_size];
        for (int i = 0; i < 10; i++) {
            // do something with the buffer
            buffer = null;
        }
    }
}