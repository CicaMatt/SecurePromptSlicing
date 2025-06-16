import java.util.*;
    
    public class CheckMod {
        public static String checkMod(String a, String b) {
            int num1 = Integer.parseInt(a);
            int num2 = Integer.parseInt(b);
            if (num1 % num2 == 0) {
                return "true";
            } else {
                return "false";
            }
        }
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter first number: ");
            int num1 = sc.nextInt();
            System.out.print("Enter second number: ");
            int num2 = sc.nextInt();
            if (checkMod(num1, num2)) {
                System.out.println(num1 + " is divisible by " + num2);
            } else {
                System.out.println(num1 + " is not divisible by " + num2);
            }
        }
    }