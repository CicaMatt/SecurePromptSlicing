import java.util.*;

public class Solution {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide one argument.");
            System.exit(0);
        }
        String input = args[0];
        System.out.println(input.trim());
        System.out.println(args[0]);
    }
}