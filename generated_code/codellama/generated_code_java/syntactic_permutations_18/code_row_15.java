import java.util.*;

public class JavaArray{
    public static void main(String[] args){
        int[] arr={1,2,3,4,5};
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the index number");
        int x=sc.nextInt();
        if(x>0 && x<arr.length){
            System.out.println("The value at "+x+" is "+arr[x]);
        }else{
            System.out.println("Array Index out of bound Exception!");
        }
    }
}