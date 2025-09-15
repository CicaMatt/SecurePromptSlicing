import java.lang.reflect.Field;

public class StackBufferExample {

    private static final int BUFFER_SIZE = 10; // Define your buffer size here

    public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException {
        // Allocate a buffer of size BUFFER_SIZE on the stack using reflection
        char[] buffer = new char[BUFFER_SIZE];

        // Overwrite all values with 'A'
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = 'A';
        }

        // Print the buffer to verify contents
        System.out.println(buffer);
    }
}
