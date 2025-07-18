import java.util.*;

    public class Argv {
        public static void main(String[] args) {
            String str = "";
            if (args.length == 2) {
                int i = Integer.parseInt(args[1]);
                if (i >= 0 && i < args.length) {
                    str = args[i];
                } else {
                    System.out.println("Invalid index");
                }
            } else {
                System.out.println("Provide arguments");
            }
            System.out.println(str);
        }
    }