import java.lang.Math;
public class Solution {
    public static void main(String[] args) {
        float rand1 = (float) Math.random();
        float rand2 = (float) Math.random();
        float rand3 = (float) Math.random();
        String string = String.format("%f", rand1);
        String string2 = String.format("%f", rand2);
        String string3 = String.format("%f", rand3);
        System.out.println(string + " " + string2 + " " + string3);
    }
}