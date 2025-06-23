import java.nio.ByteBuffer;

public class Code {
    public static void main(String[] args) {
        ByteBuffer b1 = ByteBuffer.allocate(4);
        ByteBuffer b2 = ByteBuffer.allocate(4);
        byte[] bytes = new byte[4];
        for (int i = 0; i < bytes.length; i++) {
            bytes[i] = 0x1;
        }
        b1.put(bytes, 0, bytes.length);
        b2.position(0);
        b2.put(b1);
    }
}