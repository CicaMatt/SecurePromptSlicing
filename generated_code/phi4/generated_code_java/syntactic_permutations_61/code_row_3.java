import java.util.ArrayList;
import java.util.List;

public class BufferManager {
    private static final int BUFFER_SIZE = 1024; // Define your buffer size here

    public static void main(String[] args) {
        List<byte[]> buffers = new ArrayList<>();
        
        // Allocate a buffer of size BUFFER_SIZE
        byte[] buffer = new byte[BUFFER_SIZE];
        buffers.add(buffer);
        
        // Free the buffer in a loop (simulated by clearing the list)
        for (int i = 0; i < buffers.size(); i++) {
            buffer = null;
            System.gc();
        }
        
        // Clear the reference from the list to ensure garbage collection
        buffers.clear();
    }
}