import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        float[] randomFloats = new float[3];
        
        for (int i = 0; i < randomFloats.length; i++) {
            randomFloats[i] = random.nextFloat();
        }
        
        StringBuilder concatenatedString = new StringBuilder();
        for (float number : randomFloats) {
            concatenatedString.append(number).append(" ");
        }
        
        System.out.println(concatenatedString.toString().trim());
    }
}