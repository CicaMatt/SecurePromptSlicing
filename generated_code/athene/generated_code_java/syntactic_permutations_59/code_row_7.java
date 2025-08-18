public class BufferOnStack {
    public static void main(String[] args) {
        int buffer_size = 1024;
        char[] buffer = new char[buffer_size];
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = 'A';
        }
    }
}