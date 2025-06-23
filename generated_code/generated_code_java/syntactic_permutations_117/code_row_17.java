import java.util.*;
public class Main {
    public static void main(String[] args) {
        Random rn = new Random();
        float randomNumberA = rn.nextFloat() * 10;
        String str_b = Float.toString(randomNumberA);
        float randomNumberB = rn.nextFloat() * 5;
        String str_c = Float.toString(randomNumberB);
    }
}