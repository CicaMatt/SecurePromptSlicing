public class BufferTest {
    public static void main(String[] args) {
        int buffer_size = 100; // Example buffer size, can be changed as needed

        if (buffer_size > Short.MAX_VALUE) {
            System.out.println("Error: Buffer size too large to fit in a short");
            return;
        }

        char[] stackBuffer = new char[(short) buffer_size];

        for (int i = 0; i < buffer_size; i++) {
            stackBuffer[i] = 'A';
        }

        // Example usage of the buffer
        System.out.println(new String(stackBuffer));
    }
}