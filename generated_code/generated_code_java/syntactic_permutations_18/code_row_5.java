import java.util.*;
public class ArrayIndex{
    public static void main(String[] args){
        //Declaring and initializing an int array with the values 1,2,3,4,5
        int [] x = {1,2,3,4,5};
        
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int num=sc.nextInt();
        
        //Printing the value at the index of the integer in the array
        System.out.println("The value at index "+num+" is: " + x[num]);
    }
}