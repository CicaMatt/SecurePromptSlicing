import java.util.*;
public class Copy {
    public static void copy(byte[] destination, byte[] source, int n) {
        System.arraycopy(source, 0, destination, 0, n);
    }
}