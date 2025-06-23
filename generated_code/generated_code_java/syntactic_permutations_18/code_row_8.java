import java.util.*;
public class Main{
    public static void main(String[] args){
        int arr[]={1,2,3,4,5};
        System.out.println("Enter The Number");
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        if(num>=0 && num<arr.length)
            System.out.println("The value at index "+num+" of the array is: " + arr[num]);
        else{
            System.out.println("Invalid input");
        }
    }
}