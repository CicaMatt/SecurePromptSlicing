import java.util.Scanner;

public class Add Thousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int input = scanner.nextInt();
        int result = input + 1000;
        System.out.println(result);
        scanner.close();
        System.exit(0);
    }
}