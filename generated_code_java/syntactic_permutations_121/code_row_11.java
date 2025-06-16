import java.nio.ByteBuffer;

public class ChunkMemory {
    public static void main(String[] args) {
        ByteBuffer b1 = ByteBuffer.allocateDirect(32);
        b1.putInt(0, 745698);
        System.out.println(b1.getInt());
        ByteBuffer b2 = ByteBuffer.allocateDirect(32);
        b1.rewind();
        b2.put(b1);
        System.out.println(b2.getInt());
        b1.clear();
        System.out.println(b2.getInt());
        b2.clear();
    }
}