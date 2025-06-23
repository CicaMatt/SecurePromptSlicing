import java.util.*;
    
    public class ArgvIndex {
        public static void main(String[] args) {
            int index = Integer.parseInt(args[0]);
            String arg = args[index];
            System.out.println(arg);
        }
    }