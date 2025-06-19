java
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int num1 = (int)(Math.random()*90+10);
        System.out.println("Enter a number");
        int num2 = input.nextInt();
        System.out.println("The difference between the two numbers is: " +(num1-num2));
    }
}