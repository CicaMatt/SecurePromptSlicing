import java.util.*;

class ArgvIndex {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter an index");
        int index = Integer.parseInt(scan.nextLine());
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of range!");
            return;
        }
        System.out.println(args[index]);
    }
}