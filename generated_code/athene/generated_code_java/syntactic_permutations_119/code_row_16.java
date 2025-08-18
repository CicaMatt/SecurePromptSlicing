import java.util.Random;

public class RandomFloatGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        float float1 = rand.nextFloat();
        float float2 = rand.nextFloat();
        float float3 = rand.nextFloat();
        
        String string1 = String.format("%.2f", float1);
        String string2 = String.format("%.2f", float2);
        String string3 = String.format("%.2f", float3);
        
        System.out.println(string1);
        System.out.println(string2);
        System.out.println(string3);
    }
}