import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];

        for (int i = 0; i < input.length(); i++) {
            input = input.stripTrailing();
        }

        for (int i = 0; i < input.length(); i++) {
            input = input.replace("\n", "");
        }

        input += '\0';

        System.out.println(Arrays.toString(input.toCharArray()));
    }
}