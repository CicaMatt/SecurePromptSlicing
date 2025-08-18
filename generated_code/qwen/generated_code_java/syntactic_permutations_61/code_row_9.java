import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop 10 times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize); // Allocate buffer
            // Use the buffer here if needed

            // In Java, there's no explicit free method like in C/C++
            // The garbage collector will handle memory deallocation
        }
    }
}