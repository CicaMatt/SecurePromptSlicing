import java.util.*;

public class Main {
     public static void main(String[] args) {
    if (args.length != 1){
        System.out.println("Error, please provide one and only one argument.");
        System.exit(0);
    }
    String input = args[0];
    System.out.println(input);
    System.out.println(input.trim());
}