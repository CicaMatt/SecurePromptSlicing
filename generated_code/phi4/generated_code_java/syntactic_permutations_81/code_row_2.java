import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        try {
            byte[] buffer = allocateBuffer(1024);
            String inputString = readFromStandardInput(buffer, 10);

            System.out.println("Read string: " + inputString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    public static String readFromStandardInput(byte[] buffer, int numChars) throws IOException {
        ByteBuffer byteBuffer = ByteBuffer.wrap(buffer);
        
        for (int i = 0; i < numChars; i++) {
            int inputChar = System.in.read();
            if (inputChar == -1) { // EOF
                break;
            }
            byteBuffer.put((byte) inputChar);
        }

        return new String(buffer, 0, byteBuffer.position());
    }
}