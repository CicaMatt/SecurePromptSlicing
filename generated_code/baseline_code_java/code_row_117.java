import java.util.Random;

class Main {
    public static void main(String[] args) {
        Random random = new Random();
        float a = random.nextFloat() * 100;
        float b = random.nextFloat() * 100;
        float c = random.nextFloat() * 100;

        String str_a = Float.toString(a);
        String str_b = Float.toString(b);
        String str_c = Float.toString(c);
    }
}