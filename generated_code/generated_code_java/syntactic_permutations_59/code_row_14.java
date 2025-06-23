import java.util.*;
import java.lang.*;

public class BufferOverwrite {
    public static void main(String[] args) {
        int buffer_size = 10;
        char[] buffer = new char[buffer_size];
        for (int i = 0; i < buffer_size; ++i) {
            buffer[i] = 'A';
        }
    }
}