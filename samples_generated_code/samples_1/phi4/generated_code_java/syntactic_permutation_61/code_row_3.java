public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example size, can be set to any desired value
        byte[] buffer = new byte[bufferSize];

        for (int i = 0; i < 10; i++) { // Loop example with 10 iterations
            System.out.println("Iteration " + (i + 1) + ": Buffer allocated and freed.");
            
            // Freeing the buffer by setting it to null, allowing garbage collection.
            buffer = null;
            
            // Suggesting JVM to run Garbage Collector, though not guaranteed to execute immediately.
            System.gc();
        }
    }
}