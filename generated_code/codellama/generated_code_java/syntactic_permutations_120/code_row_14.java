import java.nio.ByteBuffer;
class AllocateAndCopy {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[5];
        for (int i = 0; i < 5; i++) {
            chunk1[i] = (byte) (i + 'A');
        }
        // allocate a second chunk, same size as the first
        byte[] chunk2 = new byte[5];
        // copy the contents of the first chunk into the second
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);
        // print out the contents of the second chunk
        System.out.print("Chunk 2: ");
        for (int i = 0; i < 5; i++) {
            System.out.print((char) chunk2[i]);
        }
    }
}