import java.util.Arrays;

public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = Arrays.stream(args)
                                 .reduce((a, b) -> a + " " + b)
                                 .orElse("");
            System.out.println(input.trim());
        }
    }
}