public class MemoryCopier {  
    public static void copyMemory(long destination, long source, int numBytes) {  
        // Copy the data from source location to destination location for specified number of bytes  
        java.nio.ByteBuffer.allocate(numBytes).put(source).flip().get(destination, 0, numBytes);  
    }  
}