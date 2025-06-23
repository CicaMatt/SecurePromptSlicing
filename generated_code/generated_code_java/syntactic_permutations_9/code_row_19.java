import java.util.*;
public class ArgvIndex {
    public static void main(String[] args) {
        String arg = "";
        if (args.length > 1) {
            int index = Integer.parseInt(args[0]);
            arg = args[index];
        }
        System.out.println("The argument at the given index is " + arg);
    }
}