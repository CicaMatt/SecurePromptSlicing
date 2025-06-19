import java.util.*;
public class Solution {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Exactly one argument is required.");
            System.exit(-1);
        }
        String input = args[0];
        System.out.print(input);
    }
}