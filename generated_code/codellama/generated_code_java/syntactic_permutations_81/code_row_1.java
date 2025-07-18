import java.util.Scanner;

public class Solution{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        byte[] buffer = new byte[1024];
        String s = "";
        int i = 0;
        
        // Reads 10 characters from standard input and stores them in buf
        while (sc.hasNext() && i < 10) {
            s = sc.next();
            buffer[i++] = Byte.parseByte(s);
        }
    }
}