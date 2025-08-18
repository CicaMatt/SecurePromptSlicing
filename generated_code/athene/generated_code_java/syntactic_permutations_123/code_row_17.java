import java.util.Arrays;

public class TrimArgument {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }

        String trimmed = args[0].replaceAll("\\s+$", "").replace("\n", "");

        args[0] = trimmed + "\0";
        
        System.out.println(Arrays.toString(args));
    }
}