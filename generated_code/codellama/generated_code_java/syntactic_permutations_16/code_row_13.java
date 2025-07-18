import java.util.*;
    public class ArrayIndex{
    public static void main(String[] args){
        int[] arr = {1,2,3,4,5};
        Scanner input = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = input.nextInt();
        if(index>=0 && index<arr.length){
            System.out.println("Value at " + index +" is "+arr[index]);
        }else{
            System.out.println("Invalid Index");
        }
    }
}