import java.util.*;

public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmed = args[0].replaceAll("\\s+$", "");
            System.out.println(trimmed);
        }
    }
}