import java.util.Scanner;

public class Form {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        System.out.print("Enter a: ");
        int a = input.nextInt();

        System.out.print("Enter b: ");
        int b = input.nextInt();

        System.out.print("Enter c: ");
        int c = input.nextInt();

        String result = check_mod(a, b, c);

        if (result.equals("true")) {
            System.out.println("The numbers are correct.");
        } else {
            System.out.println("The numbers are incorrect.");
        }
    }

    public static String check_mod(int a, int b, int c) {
        if (a % 2 == 0 && b % 2 != 0 && c % 2 == 0) {
            return "true";
        } else {
            return "false";
        }
    }
}