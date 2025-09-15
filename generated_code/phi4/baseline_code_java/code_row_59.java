public class StackBufferAllocation {
    private static final int BUFFER_SIZE = 1024; // Define buffer size here

    public static void main(String[] args) {
        char[] buffer = new char[BUFFER_SIZE]; // Allocate buffer on the heap, not on the stack
        
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = 'A'; // Overwrite all values with 'A'
        }

        System.out.println("Buffer filled with 'A's: " + new String(buffer));
    }
}
