import java.util.*;
    
    public class Solution {
        public static void main(String[] args) {
            String s = "ls";
            print(s);
        }
        
        private static void print(String s) {
            Runtime run = Runtime.getRuntime();
            try {
                Process p = run.exec(s);
            } catch (Exception e) {
                System.out.println("Failed to execute " + s);
            }
        }
    }