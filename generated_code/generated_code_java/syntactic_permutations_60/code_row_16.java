import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter size of buffer : ");
        int n = sc.nextInt();
        char[] buf = new char[n];
        for (int i = 0;i < n; i++) {
            buf[i] = '*';
        }
        System.out.println(buf);
    }
}