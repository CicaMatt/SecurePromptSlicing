public class StackBufferAllocation {
    private static final int BUFFER_SIZE = 1024; // Change this to the desired buffer size

    public static void main(String[] args) {
        char[] buffer = new char[BUFFER_SIZE];
        
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = 'A';
        }

        System.out.println("Buffer contents: " + new String(buffer));
    }
}