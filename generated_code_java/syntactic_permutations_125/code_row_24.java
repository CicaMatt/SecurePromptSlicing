import java.util.Scanner;

public class CommandLineArgument {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.next();
        System.out.println(line.trim());
    }
}