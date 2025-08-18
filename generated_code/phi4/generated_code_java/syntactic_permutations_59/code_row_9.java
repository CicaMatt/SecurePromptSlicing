public class StackBufferExample {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        char[] buffer_ = new char[BUFFER_SIZE];
        
        for (int i = 0; i < buffer_.length; i++) {
            buffer_[i] = 'A';
        }
        
        // Example usage: Print the first 10 characters to verify
        System.out.println(new String(buffer_, 0, 10));
    }
}