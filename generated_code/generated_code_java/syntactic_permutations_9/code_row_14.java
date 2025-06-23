import java.util.Scanner;

public class argv_index {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter index: ");
        int idx = sc.nextInt();
        if (idx < args.length) {
            System.out.println(args[idx]);
        } else {
            System.out.println("Index out of range");
        }
    }
}