import java.util.Arrays;

public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmedArgument = Arrays.stream(args)
                                           .reduce((a, b) -> a + " " + b)
                                           .get()
                                           .trim();
            System.out.println(trimmedArgument);
        }
    }
}