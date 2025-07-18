import java.util.*;
public class Program{
    public static void main(String[] args) {
        int index = Integer.parseInt(args[1]);
        String numAsStr = args[index];
        int result = Integer.parseInt(numAsStr);
        System.out.println("Number is: " + result);
    }
}