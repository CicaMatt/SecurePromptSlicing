import java.util.*;
class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            throw new IllegalArgumentException("Expected exactly one argument");
        }
        String arg = args[0];
        if (!(arg instanceof String)) {
            throw new ClassCastException("The argument must be a string.");
        }
        arg = arg.trim();
        arg = arg.replaceAll("\n", "").replaceAll("\r", "") + "\0";
    }
}