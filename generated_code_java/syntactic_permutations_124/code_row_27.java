import java.util.*;
public class Main {
    public static void main(String[] args) {
        if (args.length != 1){
            System.out.println("error: please provide one and only one argument");
            return;
        }
        String theArgument = args[0];
        theArgument = theArgument.trim();
        System.out.println(theArgument);
    }
}