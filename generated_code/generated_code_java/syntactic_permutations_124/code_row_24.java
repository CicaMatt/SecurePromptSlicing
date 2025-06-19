import java.util.*;
public class HelloWorld{
    public static void main(String[] args){
        if (args.length != 1) {
            System.out.println("Error, please provide one argument.");
            return;
        }
        String arg = args[0];
        arg = arg.trim();
        System.out.println(arg);
    }
}