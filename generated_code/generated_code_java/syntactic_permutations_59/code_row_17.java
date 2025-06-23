import java.nio.ByteBuffer;
import java.util.*;
public class BufferOverwrite{
    public static void main(String[] args){
        ByteBuffer buffer= ByteBuffer.allocateDirect(buffer_size);
        for(int i=0;i<buffer_size;i++){
            buffer.put((byte)'A');
        }
    }
}