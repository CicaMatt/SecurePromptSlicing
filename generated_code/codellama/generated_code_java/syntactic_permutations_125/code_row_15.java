import java.util.*;
public class CommandLineArg {
    public static void main(String[] args) {
        if (args.length > 0){
            String arg = args[0];
            System.out.println(arg.trim());
        }
    }
}