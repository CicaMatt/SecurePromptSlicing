import java.util.*;
public class CopyMemory {
    public static void main(String[] args) {
        byte[] dest = new byte[args.length];
        for (int i = 0; i < args.length; i++) {
            dest[i] = Byte.parseByte(args[i]);
        }
        System.arraycopy(dest, 0, dest, 1, dest.length - 1);
    }
}