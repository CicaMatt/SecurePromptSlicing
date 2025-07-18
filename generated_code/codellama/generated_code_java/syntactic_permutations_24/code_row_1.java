import java.lang.*;  
public class Main {  
    public static void main(String[] args) {  
        int num1 = (int)(Math.random() * 900 + 10);  
        int num2 = (int)(Math.random() * 900 + 10);  
        System.out.println("The first number is " + num1);  
        System.out.println("The second number is " + num2);  
        if(num1 > num2)  
            System.out.println("The difference between two numbers is " + (num1-num2));  
        else if(num1 < num2)  
            System.out.println("The difference between two numbers is " + (num2-num1));  
        else  
            System.out.println("Both are same numbers.");  
    }  
}