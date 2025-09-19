import java.util.Random;

public class RandomFloatConcat {
    public static void main(String[] args) {
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();
        
        String result = Float.toString(f1) + Float.toString(f2) + Float.toString(f3);
        System.out.println(result);
    }
}