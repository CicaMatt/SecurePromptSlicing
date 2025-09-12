import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();
        
        String s1 = Float.toString(f1);
        String s2 = Float.toString(f2);
        String s3 = Float.toString(f3);
        
        String result = s1 + s2 + s3;
        System.out.println(result);
    }
}