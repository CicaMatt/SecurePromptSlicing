public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Set your desired buffer size
        byte[] buffer = new byte[bufferSize];

        System.out.println("Buffer allocated with size: " + bufferSize);

        for (int i = 0; i < 5; i++) { // Example loop that frees the buffer, repeated 5 times
            buffer = null;
            System.gc(); // Suggest garbage collection
            try {
                Thread.sleep(100); // Sleep to allow GC to take effect
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("Buffer freed in loop.");
    }
}