import java.util.Scanner;

public class Code {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        byte[] buf = new byte[1024];
        int i = 0;
        while (sc.hasNext() && i < 100) {
            String str = sc.next();
            for (int j = 0; j < str.length(); j++) {
                if (i == buf.length) break;
                buf[i++] = (byte) str.charAt(j);
            }
        }

        byte[] buf1 = new byte[1024];
        int k = 0;
        while (sc.hasNext() && k < 100) {
            String str1 = sc.next();
            for (int j = 0; j < str1.length(); j++) {
                if (k == buf1.length) break;
                buf1[k++] = (byte) str1.charAt(j);
            }
        }
    }
}