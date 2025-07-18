import java.util.*;
    
    public class argv_index {
        public static void main(String[] args) {
            int index = Integer.parseInt(args[0]);
            String value = args[index];
            System.out.println("Argument at index " + index + " is " + value);
        }
    }