import java.util.*;
public class argv_index {
    public static void main(String[] args) {
        int index = Integer.parseInt(args[0]); // Takes an integer input from user as a string and then converts it to an integer
        String result = args[index]; // stores the corresponding argument in result
        System.out.println(result); // prints the corresponding argument
    }
}