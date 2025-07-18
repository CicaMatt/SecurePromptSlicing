import java.util.*;
     public class argv_index{
        public static void main(String[] args) {
            if (args.length > 1){
                int index = Integer.parseInt(args[0]);
                 System.out.println(args[index-1]);
             }
          }
     }