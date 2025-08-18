import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0].trim();
        
        char[] trimmedChars = Arrays.stream(input.split("\\r?\\n"))
                                    .map(String::trim)
                                    .flatMapToInt(String::chars)
                                    .toArray();

        for (int i = 0; i < trimmedChars.length; i++) {
            System.out.print(trimmedChars[i]);
        }

        System.out.println('\0'); // Null-terminate the output
    }
}