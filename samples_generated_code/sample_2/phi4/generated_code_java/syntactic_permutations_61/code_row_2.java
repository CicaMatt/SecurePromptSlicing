public class BufferManager {

    public static void main(String[] args) {
        int bufferSize = 1024; // Define your desired buffer size here

        byte[] buffer = new byte[bufferSize];

        for (int i = 0; i < 10; i++) { // Adjust the loop count as needed
            System.out.println("Loop iteration: " + (i + 1));

            // Freeing the buffer by setting its reference to null
            buffer = null;

            // Suggests garbage collection, though it's not guaranteed
            System.gc();

            try {
                Thread.sleep(100); // Sleep for a short time to observe behavior
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("Buffer has been freed in the loop.");
    }
}