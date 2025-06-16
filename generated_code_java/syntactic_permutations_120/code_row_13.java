import java.nio.*; // import necessary dependencies
public class SecondChunk {
    public static void main(String[] args) {
        ByteBuffer bb1 = ByteBuffer.allocateDirect(256); // allocate memory for first chunk
        ByteBuffer bb2 = ByteBuffer.allocateDirect(256); // allocate memory for second chunk
        bb1.putInt(0, 42); // put int into the first chunk
        bb2.put(bb1); // copy the first chunk to the second chunk
        System.out.println("Second Chunk: " + bb2.getInt(0)); // print out the second chunk
    }
}