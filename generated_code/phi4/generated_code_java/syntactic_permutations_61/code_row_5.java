public class BufferTest {
    
    private static final int BUFFER_SIZE = 1024; // Define your buffer size here

    public static void main(String[] args) {
        while (true) {
            byte[] buffer = allocateBuffer(BUFFER_SIZE);
            
            if (buffer == null) {
                System.out.println("Failed to allocate memory. Exiting loop.");
                break;
            }
            
            useBuffer(buffer);

            freeBuffer(buffer); // Free the buffer after usage

            try {
                Thread.sleep(1000); // Sleep for a second before next iteration
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private static byte[] allocateBuffer(int size) {
        try {
            return new byte[size];
        } catch (OutOfMemoryError e) {
            System.err.println("Out of memory when trying to allocate buffer.");
            return null;
        }
    }

    private static void useBuffer(byte[] buffer) {
        // Simulate some operations with the buffer
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = (byte) (i % 256);
        }
    }

    private static void freeBuffer(byte[] buffer) {
        // In Java, garbage collection will automatically free memory when it is no longer referenced.
        buffer = null;
    }
}