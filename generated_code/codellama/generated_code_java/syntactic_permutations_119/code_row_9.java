import java.util.Random;

public class RandomFloat {

    public static void main(String[] args) {
        float rand = (float)(Math.random() * 10);
        System.out.println("rand = " + rand);
        String string = String.format("%f", rand);
        System.out.println("string = " + string);

        float rand2 = (float)(Math.random() * 10);
        System.out.println("rand2 = " + rand2);
        String string2 = String.format("%f", rand2);
        System.out.println("string2 = " + string2);

        float rand3 = (float)(Math.random() * 10);
        System.out.println("rand3 = " + rand3);
        String string3 = String.format("%f", rand3);
        System.out.println("string3 = " + string3);

    }
}