import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        ByteBuffer dest = ByteBuffer.allocate(10);
        ByteBuffer src = ByteBuffer.wrap("Hello".getBytes());
        int numberToCopy = 5;
        
        copy(dest, src, numberToCopy);
        
        System.out.println(new String(dest.array(), 0, numberToCopy));
    }

    public static void copy(ByteBuffer dest, ByteBuffer src, int numBytes) {
        byte[] temp = new byte[numBytes];
        src.get(temp);
        src.rewind();
        dest.put(temp);
    }
}