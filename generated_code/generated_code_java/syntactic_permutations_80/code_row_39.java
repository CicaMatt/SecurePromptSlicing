import java.util.Scanner;
public class Scan {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int numChars = sc.nextInt();
        System.out.println("line: " + line + "\nnumChars: " + numChars);
    }
}