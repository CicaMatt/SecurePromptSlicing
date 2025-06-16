import java.io.*;
class Main {
    public static void main(String[] args) throws IOException{
        if (args.length != 1) {
            System.err.println("Usage: java Main <string>");
            System.exit(1);
        }

        String input = args[0];
        System.out.println("input: " + input);
        input = input.trim();
        System.out.println("input (trimmed): " + input);
    }
}