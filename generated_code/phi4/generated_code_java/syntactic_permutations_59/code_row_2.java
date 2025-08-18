public class StackBuffer {
    public static void main(String[] args) {
        final int bufferSize = 128; // Define your desired buffer size here

        char[] stackBuffer = new char[bufferSize];

        for (int i = 0; i < stackBuffer.length; i++) {
            stackBuffer[i] = 'A';
        }

        System.out.println(new String(stackBuffer));
    }
}