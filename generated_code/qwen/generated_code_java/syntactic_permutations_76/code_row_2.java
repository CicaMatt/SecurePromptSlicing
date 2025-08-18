import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Assuming sizeof(person) is 16 bytes for this example
        int sizeOfPerson = 16;
        
        // Allocate a block of memory
        ByteBuffer buffer = ByteBuffer.allocateDirect(sizeOfPerson);
        buffer.order(ByteOrder.nativeOrder());

        // Set the status to 0 (assuming status is an integer at the start of the person struct)
        buffer.putInt(0, 0);

        // For demonstration, let's print the allocated memory content as integers
        for (int i = 0; i < sizeOfPerson / Integer.BYTES; i++) {
            System.out.println(buffer.getInt(i * Integer.BYTES));
        }
    }
}