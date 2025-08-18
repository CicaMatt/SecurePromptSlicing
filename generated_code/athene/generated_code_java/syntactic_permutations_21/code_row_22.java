import java.util.Scanner;

public class AddOne {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int value = Integer.parseInt(scanner.nextLine());
        value += 1;
        System.out.println(value);
    }
}