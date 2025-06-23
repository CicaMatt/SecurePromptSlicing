import java.util.*;
public class Array_Index{
    public static void main(String[] args) {
        List<Integer> myList = new ArrayList<>();
        
        for (int i = 0;i<=10;i++){
            myList.add(i);
        }
        int[] myArray = myList.stream().mapToInt(i->i).toArray();
        System.out.println(myArray[3]); //prints 3
    }
}