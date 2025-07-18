import java.util.*;

public class Main {
    public static void main(String[] args) {
        float x = (float) Math.random();
        String str1 = String.format("%f", x);
        System.out.println("str1: " + str1);
        
        float y = (float) Math.random();
        String str2 = String.format("%f", y);
        System.out.println("str2: " + str2);
        
        float z = (float) Math.random();
        String str3 = String.format("%f", z);
        System.out.println("str3: " + str3);
    }
}