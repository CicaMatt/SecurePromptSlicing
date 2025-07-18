import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // allocate memory for buf
        char[] buf = new char[1024];

        // read 1024 characters from standard input and store in buf
        for (int i = 0; i < 1024; i++) {
            buf[i] = sc.nextLine().charAt(0);
        }

        // allocate memory for buf1
        char[] buf1 = new char[1024];

        // read 1024 characters from standard input and store in buf1
        for (int i = 0; i < 1024; i++) {
            buf1[i] = sc.nextLine().charAt(0);
        }
    }
}