import java.io.*;

public class BufferExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = allocateBuffer(1024);
        readInputAndStore(buf, 10);
        System.out.println(new String(buf, 0, 10));
    }

    private static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    private static void readInputAndStore(byte[] buffer, int length) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();
        for (int i = 0; i < Math.min(length, input.length()); i++) {
            buffer[i] = (byte) input.charAt(i);
        }
    }
}