import java.nio.ByteBuffer;

public class BufferManager {

    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, you can change this value as needed

        try {
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < 10; i++) { // Loop to simulate freeing the buffer
                buffer.clear();
                System.out.println("Buffer cleared iteration: " + (i + 1));
            }

            // No need to explicitly free the buffer as it is managed by Java's garbage collector.
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}