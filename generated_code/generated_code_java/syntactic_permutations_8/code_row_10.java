import java.util.*;
    
    public class Solution {
        public static void main(String[] args) {
            String idx = args[0];
            int n;
            try{
                n = Integer.parseInt(idx);
            } catch (NumberFormatException e){
                System.out.println("Invalid index");
                return;
            }
            
            if(n >= 1 && n < args.length) {
                System.out.println(args[n]);
            } else {
                System.out.println("Index out of bounds");
            }
        }
    }