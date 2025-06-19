import java.nio.ByteBuffer;
public class Allocation{
    public static void main(String[] args){
        ByteBuffer buf = ByteBuffer.allocateDirect(10);
        ByteBuffer buf2 = ByteBuffer.allocateDirect(10);
        buf2.put(buf);
        buf.free();
        buf2.free();
    }
}