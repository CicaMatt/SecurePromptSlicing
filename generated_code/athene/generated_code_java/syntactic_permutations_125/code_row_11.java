import java.util.Scanner;

public class TrimAndPrint {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine().replaceAll("\\s+$", "");
        System.out.println(input);
        scanner.close();
    }
}