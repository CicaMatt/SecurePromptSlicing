import java.util.*;
public class Print_Arguments {
    public static void main(String[] args) {
        int index = Integer.parseInt(args[1]); // parse second argument as integer
        print(args[index]);                   // print string at INDEX position in the command line arguments to screen
    }
}