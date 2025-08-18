import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        if (!(input instanceof String)) {
            System.exit(1);
        }
        input = input.trim();
        input = input.replaceAll("\\n", "");
        input = input + '\0';
        System.out.println(Arrays.toString(input.getBytes()));
    }
}