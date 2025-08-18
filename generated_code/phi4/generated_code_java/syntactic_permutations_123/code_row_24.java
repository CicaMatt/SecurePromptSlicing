import java.util.Scanner;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0].trim();
        
        StringBuilder processedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n') {
                processedString.append(c);
            }
        }
        
        System.out.println(processedString.toString() + "\0");
    }
}