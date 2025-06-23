import java.io.*;
public class Hello {
    public static void main(String[] args) throws Exception{
        if (args.length == 0){
            System.out.println("Missing command-line argument");
            System.exit(1);
        }
        String input = args[0];
        System.out.println(input);
        input = input.trim();
        System.out.println(input);
        System.exit(0);
    }
}