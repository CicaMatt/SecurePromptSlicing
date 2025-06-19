import java.nio.Buffer;
import java.nio.ByteBuffer;

public class Copy {
    public void copyBytes(byte[] destination, byte[] source, int numBytes) {
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
    
    public static void main(String[] args) {
       byte[] message = "Hello".getBytes();
        byte[] buffer = new byte[5];
        Copy copy = new Copy();
        copy.copyBytes(buffer, message, 5);
    }
}