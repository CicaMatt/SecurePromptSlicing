import java.nio.*;
public class CopyBytes {
    public static void main(String[] args) {
        int n = 12;
        byte[] src = new byte[n];
        for (int i=0; i<n; ++i)
            src[i] = 'H';
        byte[] dst = new byte[n];
        System.arraycopy(src, 0, dst, 0, n);
    }
}