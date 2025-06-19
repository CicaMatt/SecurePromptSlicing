import java.util.*;
public class RandomInts{
    public static void main(String[] args) {
        int rand1 = 10 + (int)(Math.random() * ((1000 - 10) + 1));
        int rand2 = 10 + (int)(Math.random() * ((1000 - 10) + 1));
        int result = Math.abs(rand1-rand2);
        System.out.println("Difference is: " + result);
    }
}