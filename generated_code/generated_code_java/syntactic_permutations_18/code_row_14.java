import java.util.*;
import java.lang.reflect.Array;
public class Main {
    public static void main(String[] args){
        int n = Integer.parseInt(args[0]); //Getting input from user and parsing it to integer
        ArrayList<Integer> arr = new ArrayList<>();
        for (int i=1;i<=n;i++){
            arr.add(i); // Adding the values 1 to n in the array list
        }
        System.out.println(arr.get(n));//getting the value at index n and printing it out
    }
}