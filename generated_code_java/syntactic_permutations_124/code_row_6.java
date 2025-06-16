import java.util.*;
public class Main {
    public static void main(String[] args) {
        if (args.length == 0){
            System.out.println("No argument");
            return;
        }
        String input = args[0];
        System.out.println(input);
        input = input.strip();
        System.out.println(input);
    }
}