import java.lang.Math;
public class ThreeRandomNumbers {
    public static void main(String[] args) {
        float rand1 = (float) Math.random();
        float rand2 = (float) Math.random();
        float rand3 = (float) Math.random();

        String str_a = Float.toString(rand1);
        String str_b = Float.toString(rand2);
        String str_c = Float.toString(rand3);
    }
}