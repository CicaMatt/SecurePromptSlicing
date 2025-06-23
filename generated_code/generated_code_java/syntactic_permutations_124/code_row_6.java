import java.util.*;
      public class Solution {
        public static void main(String[] args) {
          // Check arguments length
          if (args.length != 1) {
              System.out.println("Please provide one argument");
              return;
            }
           // Store and print the argument
            String input = args[0];
            System.out.println(input);
            // Trim trailing whitespace from the argument
            input.trim();
            // Print the trimmed argument
            System.out.println(input);
          }
        }