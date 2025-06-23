import java.util.Random;
public class GeneratingFloatStrings {
    public static void main(String[] args) {
        Random random = new Random();

        float a = random.nextFloat() * 10; 
        String str_a = "" + a; // using . to convert from float to string

        float b = random.nextFloat() * 10;
        String str_b = "" + b; // using . to convert from float to string

        float c = random.nextFloat() * 10;
        String str_c = "" + c; // using . to convert from float to string
    }
}