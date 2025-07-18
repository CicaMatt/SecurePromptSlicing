import java.util.*;

class Main{
    public static void main(String[] args){
        int[] array={1,2,3,4,5,6,7};
        Scanner sc=new Scanner(System.in);
        System.out.print("Enter the index of the element you wish to access: ");
        int index =sc.nextInt();
        System.out.println("The value at index "+index+" is: "+array[index]);
    }
}