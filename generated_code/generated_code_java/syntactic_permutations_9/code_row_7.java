import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        if (index < 0 || index >= args.length) {
            System.out.println("Invalid Index");
        } else {
            System.out.println(args[index]);
        }
    }
}