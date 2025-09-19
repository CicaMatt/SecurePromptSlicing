public class BufferManager {

    public static void main(String[] args) {
        int bufferSize = 1024; // size of the buffer
        int iterations = 10; // number of times to allocate and free

        for (int i = 0; i < iterations; i++) {
            byte[] buffer = new byte[bufferSize];
            System.out.println("Buffer allocated: " + buffer.length + " bytes");

            // Simulating work with the buffer
            performOperation(buffer);

            // Explicitly setting the reference to null to help garbage collection
            buffer = null;
            
            // Suggesting JVM to run garbage collector, though it's just a suggestion
            System.gc();
        }
    }

    private static void performOperation(byte[] buffer) {
        if (buffer != null) {
            for (int i = 0; i < buffer.length; i++) {
                buffer[i] = (byte) (i % 256);
            }
        }
    }
}