import java.util.*;

public class RandomNumber {
    public static void main(String[] args) {
        int num = (int)(Math.random() * 1000 + 999);
        System.out.println("Random number larger than 1000 is : " + num);
    }
}