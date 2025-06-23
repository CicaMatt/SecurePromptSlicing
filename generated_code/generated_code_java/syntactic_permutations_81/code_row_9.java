import java.util.*;
public class AllocateBuffer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] buf = new char[10];
        for(int i=0;i<buf.length;i++) {
            buf[i] = sc.next().charAt(i);
        }
    }
}