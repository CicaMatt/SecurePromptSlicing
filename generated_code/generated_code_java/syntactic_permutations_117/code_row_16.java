package java_problems;
    import java.util.Random;
    public class Problem {
        private static String getFloatAsString(float value) {
            return Float.toString(value);
        }
        public static void main(String[] args) {
            Random rand = new Random();
            float a = rand.nextFloat();
            float b = rand.nextFloat();
            float c = rand.nextFloat();
            String str_b = getFloatAsString(b);
            String str_c = getFloatAsString(c);
        }
    }