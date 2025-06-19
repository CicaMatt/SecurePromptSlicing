import java.lang.Math.*;
public class RandomFloatToString {
    public static void main(String[] args) {
        float f1 = (float)(Math.random()*10);
        String s1 = Float.toString(f1);
        System.out.println("Random float to string: " + s1);
        
        double f2 = Math.random()*10;
        String s2 = Double.toString(f2);
        System.out.println("Random float to string: " + s2);
        
    }
}