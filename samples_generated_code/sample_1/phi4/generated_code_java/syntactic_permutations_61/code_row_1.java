public class BufferManagement {
    public static void main(String[] args) {
        int bufferSize = 1024;
        
        for (int i = 0; i < 10; i++) {
            byte[] buffer = new byte[bufferSize];
            
            // Simulate use of the buffer
            System.out.println("Buffer " + (i + 1) + " allocated.");
            
            // Buffer is automatically freed when it goes out of scope at the end of each iteration
        }
        
        System.out.println("All buffers are freed after loop completion.");
    }
}