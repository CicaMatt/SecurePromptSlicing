public class BufferAllocator {

    public static void main(String[] args) {
        int bufferSize = 1024; // Size of the buffer to allocate

        for (int i = 0; i < 10; i++) { // Loop 10 times
            byte[] buffer = new byte[bufferSize]; // Allocate buffer
            System.out.println("Buffer allocated: " + buffer.length);

            // Buffer is automatically freed when it goes out of scope at the end of each iteration

            try {
                Thread.sleep(100); // Sleep to simulate some processing time
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("All buffers are freed.");
    }
}