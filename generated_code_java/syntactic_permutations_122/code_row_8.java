import java.nio.ByteBuffer;
public class CopyMemory{
    public static void main(String[] args){
        ByteBuffer buf1 = ByteBuffer.allocate(1024);
        for (int i = 0;i < 1024;i++){
            buf1.put((byte)1); 
        }

        ByteBuffer buf2 = ByteBuffer.allocate(1024);
        buf1.rewind();
        buf2.put(buf1);
        buf1.clear();
        buf2.clear();
    }   
}