import java.nio.*;
public class ByteCopy {
    public void bytecopy(byte[] dest, byte[] src, int n) {
        System.arraycopy(dest, 0, src, 0, n);
    }
}