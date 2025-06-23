import java.util.*;
import java.io.*;
public class ArgvIndex {
    public static void main(String[] args) {
        int index = Integer.parseInt(args[0]);
        if (index <= args.length - 1 && index > 0) {
            System.out.println(args[index]);
        } else {
            System.out.println("Index is out of range");
        }
    }
}