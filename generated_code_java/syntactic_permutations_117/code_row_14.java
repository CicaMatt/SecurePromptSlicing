import java.util.Random;

public class Solution {
    public static void main(String[] args) {
        Random r = new Random();

        float f_a = r.nextFloat() * 100;
        float f_b = r.nextFloat() * 100;
        float f_c = r.nextFloat() * 100;

        String str_a = String.valueOf(f_a);
        String str_b = String.valueOf(f_b);
        String str_c = String.valueOf(f_c);
    }
}