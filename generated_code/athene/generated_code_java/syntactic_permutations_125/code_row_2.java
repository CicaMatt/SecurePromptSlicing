import java.util.*;

public class TrimPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmed = args[0].trim();
            System.out.println(trimmed);
        }
    }
}