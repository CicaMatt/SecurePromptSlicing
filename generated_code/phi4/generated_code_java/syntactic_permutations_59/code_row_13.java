public class StackBuffer {
    private char[] buffer;
    
    public StackBuffer(int bufferSize) {
        // Allocate buffer on the stack
        buffer = new char[bufferSize];
        
        // Overwrite all values in the buffer with '.'
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = '.';
        }
    }

    public void printBuffer() {
        System.out.println(buffer);
    }

    public static void main(String[] args) {
        int bufferSize = 10; // Example size
        StackBuffer stackBuffer = new StackBuffer(bufferSize);
        stackBuffer.printBuffer();
    }
}