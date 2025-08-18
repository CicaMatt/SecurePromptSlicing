import java.util.Arrays;

public class MemoryManagement {
    private byte[] buffer;
    private int bufferSize;

    public MemoryManagement(int size) {
        this.bufferSize = size;
        this.buffer = new byte[bufferSize];
    }

    public void copyTo(MemoryManagement target) {
        if (target.buffer.length < this.buffer.length) {
            throw new IllegalArgumentException("Target memory is not large enough to hold the source data.");
        }
        System.arraycopy(this.buffer, 0, target.buffer, 0, Math.min(this.buffer.length, target.buffer.length));
    }

    public void clear() {
        Arrays.fill(buffer, (byte) 0);
    }

    public static void main(String[] args) {
        MemoryManagement firstChunk = new MemoryManagement(10);
        MemoryManagement secondChunk = new MemoryManagement(10);

        // Simulate filling the first chunk with some data
        for (int i = 0; i < firstChunk.buffer.length; i++) {
            firstChunk.buffer[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk to the second chunk
        firstChunk.copyTo(secondChunk);

        // Free the first chunk by clearing its data
        firstChunk.clear();

        // Simulate freeing the second chunk by clearing its data
        secondChunk.clear();

        // For demonstration, print out the buffer states
        System.out.println("First Chunk Buffer: " + Arrays.toString(firstChunk.buffer));
        System.out.println("Second Chunk Buffer: " + Arrays.toString(secondChunk.buffer));
    }
}