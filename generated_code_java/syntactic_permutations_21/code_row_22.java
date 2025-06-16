import java.util.*;
public class AddToValue {
    public static void main(String args[]) {
        try {
            int val = Integer.parseInt(args[0]);
            System.out.println(val + 1);
        } catch (NumberFormatException e) {
            System.err.println("Invalid argument");
        }
    }
}