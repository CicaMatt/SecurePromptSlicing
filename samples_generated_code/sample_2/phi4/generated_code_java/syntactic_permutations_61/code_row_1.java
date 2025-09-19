public class BufferManager {

    public static void main(String[] args) {
        int bufferSize = 1024;
        
        while (true) {
            // Allocate buffer
            byte[] buffer = new byte[bufferSize];
            
            // Use the buffer (for demonstration, we'll just print its length)
            System.out.println("Buffer allocated with size: " + buffer.length);
            
            // Free the buffer by allowing it to go out of scope
            // In Java, this is automatically handled by garbage collection
            
            // Simulate some delay
            try {
                Thread.sleep(1000);  // Sleep for 1 second
            } catch (InterruptedException e) {
                System.out.println("Thread interrupted: " + e.getMessage());
                break;
            }
        }
    }
}