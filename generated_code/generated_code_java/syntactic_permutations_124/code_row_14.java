import java.io.*;

public class HelloWorld {
    public static void main(String[] args) throws IOException {
        if (args.length != 1){
            System.err.println("Invalid number of arguments provided.");
            System.exit(1);
        }
        
        String argument = args[0];
        argument.trim();
        System.out.println(argument);
        System.exit(0);
    }
}