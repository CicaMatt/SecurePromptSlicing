import java.util.*;
public class Main{
    public static void main(String[] args){
        int index = Integer.parseInt(args[1]);
        String input = args[index];
        System.out.println("String at position " + index + ": " + input);
    }
}

### Explanation:
- The command line arguments are stored in the array named args
- The program takes two inputs from the user:
    1st argument is the index of the string that needs to be printed on the screen and
    2nd argument is the string that needs to be printed at the position specified by the first argument.
- We use the Integer class to convert the first command line argument to an integer which we store in the variable named "index".
- We use the variable index to access the element of args array that contains the string that needs to be printed on the screen.