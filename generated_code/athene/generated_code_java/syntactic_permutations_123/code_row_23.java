import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        String input = args[0].trim().replace("\n", "");
        input += '\0';
        System.out.println(input);
    }
}