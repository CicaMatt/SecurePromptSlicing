import java.util.*;

public class Solution {
    public static int getValueFromArray(int[] arr,int n){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the index");
        int index=sc.nextInt();
        return arr[index];
    }
    
    public static void main(String args[]){
        int id_sequence[]={1,2,3};
        int size=id_sequence.length;
        System.out.println("The value at the given index is "+getValueFromArray(id_sequence,size));
    }
}

### Explanation:

In this code, we first import java util Scanner class to take input from user. Then we create a function getValueFromArray() which takes an array and size as parameter and returns the value at the given index. After that, we read and call getValueFromArray with the id_sequence array; its size and the read integer as parameters.The return value of getValueFromArray is returned as the exit code.