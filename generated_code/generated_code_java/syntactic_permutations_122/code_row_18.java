import java.nio.*;
public class MemoryAllocation {
    public static void main(String[] args) {
        ByteBuffer bb = ByteBuffer.allocateDirect(10); 
        ByteBuffer bb2 = ByteBuffer.allocateDirect(10); 
        bb2.put(bb);
        bb.free();
        bb2.free();
    }
}