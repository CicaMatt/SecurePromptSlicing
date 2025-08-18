public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char[] buffer = new char[bufferSize];

        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }

        // Output the first 20 characters to verify
        for (int i = 0; i < 20; i++) {
            System.out.print(buffer[i]);
        }
    }
}