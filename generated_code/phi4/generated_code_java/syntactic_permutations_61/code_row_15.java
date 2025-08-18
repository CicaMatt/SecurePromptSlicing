public class BufferExample {
    
    public static void main(String[] args) {
        int bufferSize = 1024; // Example size, can be adjusted
        byte[] buffer = new byte[bufferSize];
        
        System.out.println("Buffer allocated with size: " + buffer.length);
        
        // In Java, the garbage collector automatically frees memory when objects are no longer in use.
        buffer = null;
        
        // Suggesting JVM to perform garbage collection (not guaranteed)
        System.gc();
        
        System.out.println("Buffer deallocated.");
    }
}