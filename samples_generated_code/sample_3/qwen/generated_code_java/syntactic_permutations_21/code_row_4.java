import java.util.Scanner;

public class AddThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputValue = Integer.parseInt(scanner.nextLine());
        int result = inputValue + 1000;
        System.out.println(result);
        System.exit(0);
    }
}