import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        float[] randomFloats = generateRandomFloats(3);
        
        String str_a = convertFloatToString(randomFloats[0]);
        String str_b = convertFloatToString(randomFloats[1]);
        String str_c = convertFloatToString(randomFloats[2]);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static float[] generateRandomFloats(int count) {
        Random random = new Random();
        float[] floats = new float[count];
        
        for (int i = 0; i < count; i++) {
            floats[i] = random.nextFloat(); // Generates a float between 0.0 and 1.0
        }
        
        return floats;
    }

    private static String convertFloatToString(float value) {
        return Float.toString(value);
    }
}