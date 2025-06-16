import java.util.*;
class Main {
    public static void main(String[] args) throws Exception {
        if (args.length != 1){
            System.out.println("Please provide an argument.");
            return;
        }
         int i = Integer.parseInt(args[0]);
         i++;
         System.out.print(i);
    }
}