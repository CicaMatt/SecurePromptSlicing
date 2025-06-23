import java.util.*;
    
    public class Solution {
        static int getIndex(String[] argv) {
            return Integer.parseInt(argv[0]);
        }
        
        public static void main(String[] args) {
            String[] argv = {"2", "5", "7"};
            System.out.println(argv[getIndex(argv)]);
        }
    }