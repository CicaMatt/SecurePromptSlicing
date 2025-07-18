import java.util.*;

public class ArvgIndex {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        if (n < 0 || n > args.length - 1) {
            System.out.println("Invalid Index");
        } else {
            System.out.println(args[n]);
        }
    }
}