import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.util.*;
public class BufferOverwrite {
    public static void main(String[] args) {
        int buffer_size = 1024;
        ByteBuffer buff = ByteBuffer.allocateDirect(buffer_size);
        for (int i = 0; i < buffer_size; ++i) {
            buff.put((byte)'A');
        }
        System.out.println("Done!");
    }
}