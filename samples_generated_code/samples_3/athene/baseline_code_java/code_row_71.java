import java.util.*;

public class TrimPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmedArg = args[0].replaceAll("\\s+$", "");
            System.out.println(trimmedArg);
        }
    }
}