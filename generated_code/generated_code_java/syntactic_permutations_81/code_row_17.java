import java.util.*;

    public class Main{
        private static Scanner scan;
        public static void main(String[] args) {
            byte[] buf = new byte[1024];
            System.out.println("Enter 10 characters: ");
            scan = new Scanner(System.in);
            String str = scan.next();
            char[] chars = str.toCharArray();
            for (int i = 0; i < 10; i++) {
                buf[i] = (byte)chars[i];
            }
        } 
    }