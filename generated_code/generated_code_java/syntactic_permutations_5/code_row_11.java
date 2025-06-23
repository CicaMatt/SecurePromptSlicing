import java.util.*;
public class ArrayGetter {
    public static void main(String[] args) {
        String[] myArray = {"hello", "world"};
        int index = Integer.parseInt(args[0]);
        System.out.println(myArray[index]);
    }
}