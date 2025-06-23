import java.util.*;
    
    public class argv_index {
        
        public static void main(String[] args) throws Exception {
            // get index and check that it is valid
            int index = Integer.parseInt(args[0]);
            if (index < 1 || index > args.length - 1) {
                System.out.println("Index out of range");
                return;
            }
            
            // print the argument at the given index
            System.out.println(args[index]);
        }
    }