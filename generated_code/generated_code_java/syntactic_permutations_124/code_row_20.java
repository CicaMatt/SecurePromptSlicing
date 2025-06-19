import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            if (args.length != 1) {
                System.out.println("Please provide one argument.");
                return;
            }
            String input = args[0];
            System.out.print(input);
            input = input.trim();
            System.out.print(input);
        }
    }