import java.util.Scanner;

public class Add Thousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int input = Integer.parseInt(args[0]);
        int result = input + 1000;
        System.out.println(result);
        System.exit(0);
    }
}