import java.util.*;
public class argv_index{
    public static void main(String[] args) {
        if (args.length >= 2) {
            int i = Integer.parseInt(args[0]);
            String str = args[i];
            System.out.println(str);
        } else {
            System.err.println("Not enough arguments");
        }
    }
}