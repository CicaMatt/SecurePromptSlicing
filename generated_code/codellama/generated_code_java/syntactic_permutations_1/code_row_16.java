java
public class CopyBytes {
    public static void copy(int dest, int src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}