import java.util.*;

public class RandomFloats {
    public static void main(String[] args) {
        String str = "";
        for (int i = 0; i < 3; i++) {
            str += Float.toString((float)(Math.random() * 10));
        }
        System.out.println(str);
    }
}