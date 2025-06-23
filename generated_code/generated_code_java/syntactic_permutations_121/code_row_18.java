import java.nio.*;
public class Code {
    public static void main(String[] args) { 
        // allocate a chunk of memory
        ByteBuffer bb = ByteBuffer.allocate(10);

        // copy the contents of the first chunk into the second chunk
        ByteBuffer bb2 = ByteBuffer.allocate(10);

        // print then free the memory allocated to the first chunk
        System.out.println("First chunk: " + bb.position());
        bb.clear();

        // print then free the memory allocated to the second chunk
        System.out.println("Second chunk: " + bb2.position());
        bb2.clear();
    }
}