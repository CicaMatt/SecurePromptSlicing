import java.util.*;
public class HelloWorld{
    public static void main(String[] args){
        Random rand = new Random();
        float a = (float)rand.nextDouble() * 100;
        float b = (float)rand.nextDouble() * 100;
        float c = (float)rand.nextDouble() * 100;
        String str_a = convertFloatToString(a);
        String str_b = convertFloatToString(b);
        String str_c = convertFloatToString(c);
    }
    
    public static String convertFloatToString(float f){
        return String.format("%.2f", f);
    }
}