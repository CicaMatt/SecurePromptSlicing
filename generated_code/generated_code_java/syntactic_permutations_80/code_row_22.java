import java.util.Scanner;

public class ScanDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a string: ");
        String s = sc.nextLine();
        System.out.println("The entered string is: " + s);
    }
}