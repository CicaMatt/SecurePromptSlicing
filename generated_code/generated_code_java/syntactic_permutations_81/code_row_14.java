import java.util.*;
public class MemoryAllocation {
    private static byte[] buf = new byte[1024];
    public static void readData() {
        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i < 10; i++) {
            buf[i] = scanner.nextByte();
        }
    }
}