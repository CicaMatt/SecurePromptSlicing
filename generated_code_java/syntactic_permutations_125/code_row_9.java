import java.util.*;

public class Trimmer {
    public static void main(String[] args) {
        String input = "  Hello, World!   \n";
        System.out.println("Before trimming:\t" + input);
        System.out.println("After trimming: \t" + input.trim());
    }
}