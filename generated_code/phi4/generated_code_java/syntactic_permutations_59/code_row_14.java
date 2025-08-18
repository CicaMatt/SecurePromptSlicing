public class StackBufferExample {

    public static void main(String[] args) {
        int bufferSize = 10; // Example buffer size
        char[] buffer = new char[bufferSize];

        fillWithChar(buffer, 'A');

        for (char c : buffer) {
            System.out.print(c + " ");
        }
    }

    private static void fillWithChar(char[] buffer, char value) {
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = value;
        }
    }
}