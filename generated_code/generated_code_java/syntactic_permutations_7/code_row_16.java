import java.util.Scanner; // Scanner class for reading console input
    public class Solution {
    	public static void main(String[] args) {
            int INDEX = Integer.parseInt(args[1]);  // parsing string to integer and storing in a variable
            System.out.println(args[INDEX]);        // printing the command line argument at specified index
        }
    }