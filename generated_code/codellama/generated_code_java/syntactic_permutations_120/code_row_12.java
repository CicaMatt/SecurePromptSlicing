import java.nio.ByteBuffer;

public class ByteBufferCopy {
    public static void main(String[] args) {
        // create byte buffer of 10 bytes
        ByteBuffer bb = ByteBuffer.allocateDirect(10);
        
        // fill with some test data
        for (int i = 0; i < 10; i++) {
            bb.put((byte)i);
        }
        bb.flip();
        
        // create a copy of the buffer
        ByteBuffer copy = ByteBuffer.allocateDirect(bb.limit());
        copy.put(bb);
        copy.flip();
        
        // print out copied data
        while (copy.hasRemaining()) {
            System.out.print((char)copy.get() + ", ");
        }
    }
}