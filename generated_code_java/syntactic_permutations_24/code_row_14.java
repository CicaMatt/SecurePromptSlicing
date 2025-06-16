import java.util.Random;

public class Solution {
    public static void main(String[] args) {
        int first = new Random().nextInt(1000 - 10 + 1) + 10;
        int second = new Random().nextInt(1000 - 10 + 1) + 10;
        System.out.println(first);
        System.out.println(second);
        System.out.println("The result of the calculation is: " + (first - second));
    }
}