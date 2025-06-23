import java.util.*;
public class Memory {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        char[] buf = new char[1024];
        int size = 0;
        if (s.hasNext()) {
            String str = s.next();
            for (int i = 0; i < str.length() && i < 1024; i++) {
                buf[i] = str.charAt(i);
                size++;
            }
        }
        System.out.println("Number of characters read: " + size);
        s.close();
    }
}