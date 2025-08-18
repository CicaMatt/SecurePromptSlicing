public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop to allocate and free buffer 10 times
            byte[] buffer = new byte[bufferSize];
            System.out.println("Buffer allocated: " + buffer.length);

            // Simulate using the buffer
            for (int j = 0; j < buffer.length; j++) {
                buffer[j] = (byte) (j % 256);
            }

            // Freeing the buffer by setting it to null
            buffer = null;
            System.gc(); // Request garbage collection

            // Delay to simulate time between allocations
            try {
                Thread.sleep(100); // Sleep for 100 milliseconds
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("Buffer freed.");
        }
    }
}