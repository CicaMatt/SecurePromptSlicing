import java.util.*;
public class Main {
    public static void main(String[] args) {
        String arg = args[1];
        int index = Integer.parseInt(args[2]);
        int number = Integer.parseInt(arg);
        System.out.println("The argument at position " + index + " is: " + number);
    }
}