public class BufferManager {

    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        byte[] buffer = new byte[bufferSize];

        try {
            for (int i = 0; i < 10; i++) { // Example loop to free buffer multiple times
                performOperation(buffer);
                buffer = null;
                
                if (i % 2 == 0) { // Simulate freeing memory by nullifying the buffer on even iterations
                    System.gc(); // Request garbage collection
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void performOperation(byte[] buffer) {
        if (buffer != null) {
            for (int i = 0; i < buffer.length; i++) {
                buffer[i] = (byte) (i % 256); // Example operation on the buffer
            }
        }
    }
}