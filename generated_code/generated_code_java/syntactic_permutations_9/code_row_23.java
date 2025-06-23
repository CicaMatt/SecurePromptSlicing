import java.util.*;
public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length == 1) {
            System.out.println("ERROR");
        } else {
            int index = Integer.parseInt(args[0]);
            if (index >= args.length - 1) {
                System.out.println("ERROR");
            } else {
                System.out.println(args[index + 1]);
            }
        }
    }
}