public class BufferAllocator {
    public static void main(String[] args) {
        final int ITERATIONS = 10;
        byte[] buffer;

        for (int i = 0; i < ITERATIONS; i++) {
            // Allocate buffer
            buffer = new byte[1024];
            
            // Simulate using the buffer
            System.out.println("Iteration " + (i + 1) + ": Buffer allocated with size: " + buffer.length);

            // Freeing the buffer by nullifying it
            buffer = null;

            // Suggest to JVM to perform GC, though not guaranteed
            System.gc();

            // Sleep to allow time for garbage collection
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("Buffer allocation and deallocation complete.");
    }
}