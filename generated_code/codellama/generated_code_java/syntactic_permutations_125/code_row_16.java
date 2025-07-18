import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("Please enter a command line argument");
        } else {
            String arg = args[0];
            String trimmedArg = arg.trim();
            System.out.println(arg);
        }
    }
}