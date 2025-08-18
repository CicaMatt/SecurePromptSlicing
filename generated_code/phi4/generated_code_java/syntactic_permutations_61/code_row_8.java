public class BufferManager {

    public static void main(String[] args) {
        final int bufferSize = 1024; // Size of the buffer
        final int iterations = 10;   // Number of times to allocate and free

        for (int i = 0; i < iterations; i++) {
            byte[] buffer = new byte[bufferSize]; // Allocate buffer
            System.out.println("Allocated buffer " + i);
            
            // Simulate some operation with the buffer
            performOperation(buffer);

            // Explicitly nullify reference to allow garbage collection
            buffer = null;
            System.gc(); // Suggest garbage collector to run

            System.out.println("Freed buffer " + i);
        }
    }

    private static void performOperation(byte[] buffer) {
        // Simulate some operations on the buffer
        for (int j = 0; j < buffer.length; j++) {
            buffer[j] = (byte) (j % 256); // Example operation: fill with data
        }
    }
}