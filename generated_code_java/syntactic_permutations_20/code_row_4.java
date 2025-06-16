import java.util.*;
public class Offset {
    public static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Offset number");
        } else {
            try {
                int num = Integer.parseInt(args[0]);
                System.out.println(num + OFFSET);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input.");
            }
        }
    }
}