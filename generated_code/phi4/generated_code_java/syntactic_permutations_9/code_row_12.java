import java.util.Scanner;

public class ArgvIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = scanner.nextInt();

        if (index < 1 || index >= args.length) {
            System.out.println("Invalid index.");
        } else {
            System.out.println(args[index]);
        }
    }
}