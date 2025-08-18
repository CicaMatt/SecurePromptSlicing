public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 10; // Example size for the buffer
        char[] buffer_ = new char[bufferSize];
        
        for (int i = 0; i < buffer_.length; i++) {
            buffer_[i] = 'A';
        }
        
        // Print the buffer to verify it's filled with 'A'
        System.out.println(new String(buffer_));
    }
}