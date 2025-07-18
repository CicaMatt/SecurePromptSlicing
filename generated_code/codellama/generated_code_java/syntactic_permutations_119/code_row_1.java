import java.util.Random;
public class Test {
    public static void main(String[] args) {
        Random r = new Random();

        float x1 = r.nextFloat();  
        float x2 = r.nextFloat();
        float x3 = r.nextFloat();
        String string = String.format("%f", x1);
        String string2 = String.format("%f", x2);
        String string3 = String.format("%f", x3);

    }
}