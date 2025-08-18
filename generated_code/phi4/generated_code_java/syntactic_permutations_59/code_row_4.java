public class BufferStackAllocation {
    private static final int BUFFER_SIZE = 1024; // Define your buffer size here

    public static void main(String[] args) {
        char[] buffer = new char[BUFFER_SIZE];
        
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = 'A';
        }

        // Example usage: Print the buffer content
        System.out.println(new String(buffer));
    }
}