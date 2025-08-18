import java.lang.System;

public class CommandLineArgumentFetcher {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Index out of bounds");
            System.exit(1);
        }
        String result = fetchValueAt(args, Integer.parseInt(args[1]));
        System.out.println(result);
    }

    public static String fetchValueAt(String[] argv, int index) {
        if (index < 0 || index >= argv.length) {
            return "Index out of bounds";
        }
        return argv[index];
    }
}