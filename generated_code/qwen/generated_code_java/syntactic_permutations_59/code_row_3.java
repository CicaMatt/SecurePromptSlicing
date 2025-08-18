public class BufferAllocator {
    public static void main(String[] args) {
        final int buffer_size = 1024;
        char[] buffer = new char[buffer_size];
        
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] = 'A';
        }
    }
}