public class Main {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char[] buffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = 'A';
        }
        
        // To verify the buffer content, you can print it out
        System.out.println(new String(buffer));
    }
}