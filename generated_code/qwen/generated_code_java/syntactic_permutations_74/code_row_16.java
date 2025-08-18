import java.nio.ByteBuffer;

public class Main {
    public static void main(String[] args) {
        int sizeofPerson = 16; // Assuming a simple person structure with fixed size for demonstration
        ByteBuffer personBlock = ByteBuffer.allocate(sizeofPerson);
        personBlock.clear();
        personBlock.put(new byte[sizeofPerson]); // Set all bytes to 0

        // For demonstration, let's assume the first 4 bytes are an integer (age) and next 12 bytes are a name (String)
        personBlock.putInt(0); // Setting age to 0
        for (int i = 4; i < sizeofPerson; i++) {
            personBlock.put(i, (byte) 0); // Setting name bytes to 0
        }

        System.out.println("Allocated and zeroed memory block for a person.");
    }
}