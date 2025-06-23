import java.util.*;
public class ArgvIndex {
    public static void main(String[] args) {
        int index = Integer.parseInt(args[0]);
        System.out.println("Argument at index " + index + ": " + args[index]);
    }
}