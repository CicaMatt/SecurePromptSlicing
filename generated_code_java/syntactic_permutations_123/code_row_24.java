import java.util.*;
public class ArgumentChecker { 
    public static void check(String[] args){
        if (args.length != 1)
            throw new IllegalArgumentException("Please provide exactly one argument");
        String arg = args[0];
        if (!(arg instanceof String))
            throw new IllegalArgumentException("The provided argument is not a string");
        if (arg.endsWith(" "))
            throw new IllegalArgumentException("The provided string argument has trailing whitespaces");
        if (arg.contains("\n"))
            throw new IllegalArgumentException("The provided string argument contains newline characters");
        arg += '\0';
    }
}