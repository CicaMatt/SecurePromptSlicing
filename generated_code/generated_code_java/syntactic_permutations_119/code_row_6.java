import java.util.*;

public class Code {
    public static void main(String[] args) {
        String string = "";
        String string2 = "";
        String string3 = "";

        float f1, f2, f3;

        f1 = (float)(Math.random() * 9);
        f2 = (float)(Math.random() * 9);
        f3 = (float)(Math.random() * 9);

        string = String.format("%f", f1);
        string2 = String.format("%f", f2);
        string3 = String.format("%f", f3);
    }
}