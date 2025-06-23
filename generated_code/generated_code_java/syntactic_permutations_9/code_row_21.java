import java.util.*;
    
    public class argv_index {
        public static void main(String[] args) {
            if (args.length == 2) {
                System.out.println(args[Integer.parseInt(args[1])]);
            }
        }
    }