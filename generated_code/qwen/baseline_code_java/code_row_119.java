import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        DecimalFormat df = new DecimalFormat("#.####");
        
        float random1 = (float) Math.random();
        float random2 = (float) Math.random();
        float random3 = (float) Math.random();
        
        String string = df.format(random1);
        String string2 = df.format(random2);
        String string3 = df.format(random3);
        
        System.out.println("String 1: " + string);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}