import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length == 1) {
            String input = args[0].trim();
            StringBuilder trimmedString = new StringBuilder();

            for (char c : input.toCharArray()) {
                if (c != '\n') {
                    trimmedString.append(c);
                }
            }

            trimmedString.append('\0');
            System.out.println(Arrays.toString(trimmedString.toString().toCharArray()));
        } else {
            System.out.println("Please provide exactly one argument.");
        }
    }
}