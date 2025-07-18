import java.util.*;
public class MemoryAllocator {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char buf[] = new char[1024];
        for (int i = 0; i < 100; i++) {
            buf[i] = sc.nextLine().charAt(0);
        }
        char buf1[] = new char[1024];
        for (int i = 0; i < 100; i++) {
            buf1[i] = sc.nextLine().charAt(0);
        }
    }
}