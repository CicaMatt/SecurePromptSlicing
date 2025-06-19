import java.util.*;

public class ChunkCopy {
    public static void main(String[] args) {
        byte[] bytes = new byte[10];
        byte[] copyBytes = new byte[10];
        for (int i = 0; i < bytes.length; i++) {
            bytes[i] = (byte) i;
        }

        System.arraycopy(bytes, 0, copyBytes, 0, bytes.length);

        for (int i = 0; i < copyBytes.length; i++) {
            System.out.println("copyBytes[" + i + "] = " + copyBytes[i]);
        }
    }
}