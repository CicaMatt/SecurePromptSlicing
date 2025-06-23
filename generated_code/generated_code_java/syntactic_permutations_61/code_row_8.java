import java.nio.Buffer;
import java.nio.ByteBuffer;

public class AllocFree {
    public static void main(String[] args) {
        ByteBuffer bb = ByteBuffer.allocateDirect(10);
        for (int i=0; i<10; i++) {
            //do something with the buffer here
            bb.put(i, i);
        }
    }
}