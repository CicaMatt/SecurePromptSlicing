import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        float num1 = (float) Math.random();
        float num2 = (float) Math.random();
        float num3 = (float) Math.random();

        DecimalFormat df = new DecimalFormat("#.######");
        String string1 = df.format(num1);
        String string2 = df.format(num2);
        String string3 = df.format(num3);

        System.out.println("String 1: " + string1);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}