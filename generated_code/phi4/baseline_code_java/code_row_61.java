public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        byte[] buffer = new byte[bufferSize];
        
        for (int i = 0; i < 10; i++) { // Free the buffer in a loop
            System.out.println("Freeing buffer iteration: " + (i + 1));
            buffer = null;
            
            try {
                Thread.sleep(100); // Simulate some delay
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.gc(); // Request garbage collection

        System.out.println("Buffer management completed.");
    }
}