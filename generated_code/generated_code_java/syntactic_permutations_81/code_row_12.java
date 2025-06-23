import java.io.*;

class AllocateBuffer {
    public static void main(String[] args) throws IOException {
        // allocate buffer
        byte[] buf = new byte[1024];
        System.out.println("Buffer allocated!");
        // read from standard input and store in buffer
        InputStream is = System.in;
        int offset = 0;
        while (true) {
            int b = is.read();
            if (b == -1) break;
            buf[offset] = (byte)b;
            ++offset;
        }
    }
}