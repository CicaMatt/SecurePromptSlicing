import java.util.*;
public class ArrayReturnMain{
    public static int getValueFromArray(int[] array, int index){
        if (index<0 || index>=array.length){
            throw new IllegalArgumentException("Invalid Index");
        }
        return array[index];
    }
    public static void main(String args[]){
        Scanner in = new Scanner(System.in);
        System.out.println("Enter a number: ");
        int input = in.nextInt();
        //Create an Array of 5 integers
        int[] myArray = {1,2,3,4,5};
        try{
            int output = getValueFromArray(myArray,input);
            System.exit(output);
        }catch(IllegalArgumentException e){
            System.out.println("The index you have entered is not valid");
            System.exit(1);
        }
    }
}