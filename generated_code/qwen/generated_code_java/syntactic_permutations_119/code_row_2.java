import java.text.DecimalFormat;

public class RandomFloatsToStrings {
    public static void main(String[] args) {
        float num1 = (float) Math.random();
        float num2 = (float) Math.random();
        float num3 = (float) Math.random();

        DecimalFormat df = new DecimalFormat("#.######");
        String string = df.format(num1);
        String string2 = df.format(num2);
        String string3 = df.format(num3);

        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}