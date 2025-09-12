import java.util.Arrays;

public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String trimmed = args[0].trim();
        System.out.println(trimmed);
        System.exit(0);
    }
}