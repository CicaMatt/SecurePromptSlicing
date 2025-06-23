import java.util.*;
public class MemoryAllocation {
    private static final int BUF_SIZE = 1024;
    public void allocBuf() {
        char[] buf = new char[BUF_SIZE];
        System.out.println("Enter 100 characters:");
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        for (int i = 0; i < BUF_SIZE && i < str.length(); i++) {
            buf[i] = str.charAt(i);
        }
    }
}