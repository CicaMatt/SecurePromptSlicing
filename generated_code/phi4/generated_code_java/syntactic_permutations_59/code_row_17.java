public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 10; // Example buffer size

        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = 'A';
        }

        System.out.println("Buffer content: " + new String(buffer));
    }
}