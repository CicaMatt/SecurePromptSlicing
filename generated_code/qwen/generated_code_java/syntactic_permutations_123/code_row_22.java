import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        for (int i = 0; i < input.length(); i++) {
            input = input.trim();
            input = input.replaceAll("\\n", "");
        }

        input += '\0';

        System.out.println(Arrays.toString(input.toCharArray()));
    }
}