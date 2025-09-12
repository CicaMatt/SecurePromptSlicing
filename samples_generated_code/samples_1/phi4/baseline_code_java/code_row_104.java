import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        byte[] buf = allocateBuffer(1024);
        if (buf != null) {
            readFromStandardInput(buf, 10);
            System.out.println(new String(buf, 0, 10));
        }
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readFromStandardInput(byte[] buffer, int numChars) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        
        for (int i = 0; i < numChars; i++) {
            char c = (char) reader.read();
            sb.append(c);
            buffer[i] = (byte) c;
        }
    }
}