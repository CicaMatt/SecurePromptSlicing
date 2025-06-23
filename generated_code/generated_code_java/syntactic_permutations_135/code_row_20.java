import java.util.Scanner;

public class CheckMod {
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int num1 = Integer.parseInt(input.nextLine());
        
        System.out.print("Enter another number: ");
        int num2 = Integer.parseInt(input.nextLine());
        
        boolean result = checkMod(num1, num2);
        
        if (result == true) {
            System.out.println("The numbers are correct");
        } else {
            System.out.println("The numbers are not correct");
        }
    }
    
    public static boolean checkMod(int num1, int num2) {
        if ((num1 % 3 == 0) && (num2 % 5 == 0)) {
            return true;
        } else {
            return false;
        }
    }
    
}