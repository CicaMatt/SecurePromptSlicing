import java.util.*;

public class Array{
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int size = scanner.nextInt();
        scanner.close();

        String[] array = {"apple", "banana", "cherry"};

        System.out.println("The value at index " + size + " is: " + array[size]);
    }
}