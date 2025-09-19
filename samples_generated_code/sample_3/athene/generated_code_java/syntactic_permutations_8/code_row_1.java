import java.lang.System;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentFetcher <index> [other arguments]");
            return;
        }
        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("Index must be an integer.");
            return;
        }
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }
        System.out.println(args[index]);
    }
}