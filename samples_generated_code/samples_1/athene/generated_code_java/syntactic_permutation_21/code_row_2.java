import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();
        number += 1000;
        System.out.println(number);
        System.exit(0);
    }
}