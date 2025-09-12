import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = new byte[1024];
        Arrays.fill(source, (byte) 65); // Fill with 'A' for demonstration

        byte[] destination = new byte[source.length];
        System.arraycopy(source, 0, destination, 0, source.length);

        for (byte b : destination) {
            System.out.print((char) b);
        }
    }
}