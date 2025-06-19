import java.util.*;

public class Copy {
    public static void main(String[] args) {
        int bytes = 16;
        long destination = 5000;
        long source = 8000;

        // The copy function copies a number of bytes from one memory location is the destination; the second argument is the source and the third argument is the number of bytes to copy.
        copy(destination, source, bytes);
    }

    public static void copy (long destination, long source, int bytes) {
        for (int i = 0; i < bytes; i++) {
            unsafe.putByte(destination++, unsafe.getByte(source++));
        }
    }
}