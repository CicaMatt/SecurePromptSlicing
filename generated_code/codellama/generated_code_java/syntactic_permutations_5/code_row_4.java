import java.util.*;
public class Main{
    public static void main(String[] args) { 
        List<Integer> numbers = Arrays.asList(10,20,30,40);
        int i = Integer.parseInt(args[0]);
        System.out.println(numbers.get(i));
    }
}