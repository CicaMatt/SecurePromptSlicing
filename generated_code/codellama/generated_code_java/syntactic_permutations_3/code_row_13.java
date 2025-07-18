import java.nio.*;
public class Hello{
    public static void main(String[] args) {
        byte[] hello = {'H', 'e', 'l', 'l', 'o'};
        ByteBuffer dst = ByteBuffer.allocate(1024);
        ByteBuffer src = ByteBuffer.wrap(hello);
        copyBytes(dst, src, 5);
    }
    
    public static void copyBytes(ByteBuffer destination, ByteBuffer source, int n) {
        for (int i = 0; i < n; i++) {
            destination.put(source.get());
        }
    }
}