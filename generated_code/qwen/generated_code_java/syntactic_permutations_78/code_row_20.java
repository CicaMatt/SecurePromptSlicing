import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = 16; // Assuming each person is represented by 4 integers (e.g., ID, age, height, weight)
        ByteBuffer buffer = ByteBuffer.allocateDirect(personSize * Integer.BYTES);
        IntBuffer intBuffer = buffer.asIntBuffer();

        for (int i = 0; i < personSize / Integer.BYTES; i++) {
            intBuffer.put(i, 0);
        }

        // Assuming the first integer is the ID
        System.out.println("ID: " + intBuffer.get(0));
    }
}