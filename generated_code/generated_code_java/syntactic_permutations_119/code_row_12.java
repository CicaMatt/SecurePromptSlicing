import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        float num1 = (float)(Math.random()*10);
        System.out.println("num1: " + num1);

        String str1 = sprintf("%f", num1);
        System.out.println(str1);

        float num2 = (float)(Math.random()*10);
        System.out.println("num2: " + num2);

        String str2 = sprintf("%f", num2);
        System.out.println(str2);

        float num3 = (float)(Math.random()*10);
        System.out.println("num3: " + num3);

        String str3 = sprintf("%f", num3);
        System.out.println(str3);
    }
}