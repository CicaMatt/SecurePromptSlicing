import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1023];
        int charsRead = scanner.findWithinHorizon(".{0,1023}\n", 1024).length() - 1;
        System.out.println(charsRead);
    }
}