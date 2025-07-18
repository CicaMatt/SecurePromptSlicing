import java.util.*;
    
    public class ArrayIndex {
        public static void main(String[] args) {
            int array[] = new int[args.length];
            for (int i = 0; i < args.length; i++) {
                array[i] = Integer.parseInt(args[i]);
            }
    
            System.out.println(array);
        }
    }