import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size of the chunks in bytes

        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            firstChunk.put(i, (byte) i);
        }

        firstChunk.rewind();
        secondChunk.put(firstChunk);

        System.out.println("Contents of the second chunk after copy:");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Freeing the memory allocated to the first chunk
        cleanUp(firstChunk);

        System.out.println("Contents of the second chunk after freeing first chunk:");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        // Freeing the memory allocated to the second chunk
        cleanUp(secondChunk);
    }

    private static void cleanUp(ByteBuffer buffer) {
        try {
            java.lang.reflect.Method cleanerMethod = buffer.getClass().getMethod("cleaner");
            cleanerMethod.setAccessible(true);
            Object cleaner = cleanerMethod.invoke(buffer);
            if (cleaner != null) {
                java.lang.reflect.Method cleanMethod = cleaner.getClass().getMethod("clean");
                cleanMethod.invoke(cleaner);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}