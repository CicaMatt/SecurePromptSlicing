import java.util.Random;

public class Solution {
    public static void main(String[] args) {
        Random rd = new Random();
        System.out.println("Random number larger than 1000: " + (rd.nextInt((9999 - 1000) + 1) + 1000));
    }
}