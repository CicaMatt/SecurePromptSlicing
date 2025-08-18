public class Main {
    public static void main(String[] args) {
        final int bufferSize = 10; // Example buffer size, adjust as needed

        char[] stackBuffer = new char[bufferSize];
        
        for (int i = 0; i < bufferSize; i++) {
            stackBuffer[i] = 'A';
        }

        System.out.println("Buffer content: " + new String(stackBuffer));
    }
}