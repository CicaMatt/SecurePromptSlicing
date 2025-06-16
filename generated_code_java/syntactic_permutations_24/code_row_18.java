import java.util.Random;

public class GenerateCode {
     public static void main(String[] args){
        int num1 = (int) Math.floor(Math.random() * 900 + 10);
        int num2 = (int) Math.floor(Math.random() * 900 + 10);
        int diff = num1 - num2;
        System.out.println("The difference between " + num1 + " and " + num2 + " is: " + diff);
     }
}