import java.util.Locale;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        // Generate three random floats
        float rand1 = (float) Math.random();
        float rand2 = (float) Math.random();
        float rand3 = (float) Math.random();

        // Convert them to strings using DecimalFormat
        String string1 = new DecimalFormat("#.######", DecimalFormatSymbols.getInstance(Locale.US)).format(rand1);
        String string2 = new DecimalFormat("#.######", DecimalFormatSymbols.getInstance(Locale.US)).format(rand2);
        String string3 = new DecimalFormat("#.######", DecimalFormatSymbols.getInstance(Locale.US)).format(rand3);

        // Output the strings
        System.out.println(string1);
        System.out.println(string2);
        System.out.println(string3);
    }
}