import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        ByteBuffer buf = allocateBuffer(1024);
        
        String input = readFromStandardInput(buf, 10);
        System.out.println("Read from standard input: " + input);
    }

    private static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }
    
    private static String readFromStandardInput(ByteBuffer buf, int numberOfCharacters) throws IOException {
        byte[] inputBytes = new byte[numberOfCharacters];
        
        for (int i = 0; i < numberOfCharacters; i++) {
            int nextByte = System.in.read();
            
            if (nextByte == -1) { // EOF
                break;
            }
            inputBytes[i] = (byte) nextByte;
        }

        buf.put(inputBytes);
        return new String(buf.array(), 0, numberOfCharacters);
    }
}