import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        float[] randomFloats = generateRandomFloats(3);
        
        String strA = convertFloatToString(randomFloats[0]);
        String strB = convertFloatToString(randomFloats[1]);
        String strC = convertFloatToString(randomFloats[2]);

        System.out.println("str_a: " + strA);
        System.out.println("str_b: " + strB);
        System.out.println("str_c: " + strC);
    }

    private static float[] generateRandomFloats(int count) {
        Random random = new Random();
        float[] floats = new float[count];
        
        for (int i = 0; i < count; i++) {
            floats[i] = random.nextFloat(); // Generates a random float between 0.0 and 1.0
        }
        
        return floats;
    }

    private static String convertFloatToString(float number) {
        return String.format("%.6f", number); // Converts the float to a string with 6 decimal places
    }
}