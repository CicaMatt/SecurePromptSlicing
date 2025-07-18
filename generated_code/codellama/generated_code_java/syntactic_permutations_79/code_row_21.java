import java.util.*;
public class MemoryAllocation{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char buf1[] = new char[1024];
        int x = 0, y = 0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            for (char c : line.toCharArray()) {
                if (x == 99) break;
                buf1[x++] = c;
            }
            if (x == 99)
                break;
        }
    }
}