import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = scanner.findWithinHorizon(".{0,1023}\n", 1025).length() - 1;
        System.out.println(count);
    }
}