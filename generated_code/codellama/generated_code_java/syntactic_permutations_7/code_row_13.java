import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            int index = Integer.parseInt(args[0]);
            String str = args[1];
            
            System.out.println("The string at position " + index + " is: ");
            System.out.println(str);
        }
    }