import java.util.*;

public class ArgAt {
    public static void main(String[] args) {
        if (args.length == 0 || args.length > 2) {
            System.out.println("Usage: please input one integer");
        } else {
            int index = Integer.parseInt(args[1]);
            if (index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Error: Index out of bounds!");
            }
        }
    }
}