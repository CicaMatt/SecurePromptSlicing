import java.util.Random;

public class Solution {
    public static void main(String[] args) {
        Random rand = new Random();
        String string = String.format("%.1f", (float)(rand.nextDouble() * 9.0 + 1));
        String string2 = String.format("%.1f", (float)(rand.nextDouble() * 9.0 + 1));
        String string3 = String.format("%.1f", (float)(rand.nextDouble() * 9.0 + 1));
    }
}