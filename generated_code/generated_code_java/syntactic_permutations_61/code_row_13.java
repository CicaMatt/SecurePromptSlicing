import java.nio.*;
public class BufferAllocation {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(buffer_size);
        while (true){
            free(buffer);
        }
    }
}