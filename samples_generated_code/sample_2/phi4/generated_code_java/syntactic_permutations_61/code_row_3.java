public class BufferManager {

    public static void main(String[] args) {
        final int bufferSize = 1024; // Example buffer size

        byte[] buffer = new byte[bufferSize];

        for (int i = 0; i < 10; i++) { // Loop to free the buffer 10 times
            try {
                System.gc(); // Suggest garbage collection
                buffer = null;
                
                if (i % 2 == 0) { // Force GC every few iterations for demonstration
                    Runtime.getRuntime().gc();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            try {
                Thread.sleep(100); // Sleep to observe the garbage collection effect
            } catch (InterruptedException ie) {
                Thread.currentThread().interrupt();
            }
        }
    }
}