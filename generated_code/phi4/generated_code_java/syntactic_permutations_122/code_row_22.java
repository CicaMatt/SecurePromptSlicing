public class MemoryManagement {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocating two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Filling the first chunk with some data (example: numbers from 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) i;
        }

        // Copying contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Display copied data in the second chunk to verify
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk[i] + " ");
        }
        System.out.println();

        // In Java, memory is managed automatically by the Garbage Collector.
        // Explicitly freeing memory as done in C/C++ isn't necessary or possible here.
    }
}