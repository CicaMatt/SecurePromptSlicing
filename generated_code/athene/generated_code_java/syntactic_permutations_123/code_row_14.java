import java.util.Arrays;

public class ArgumentProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        String arg = args[0].trim();
        
        while (arg.endsWith("\n")) {
            arg = arg.substring(0, arg.length() - 1);
        }

        args[0] = arg + "\0";
    }
}