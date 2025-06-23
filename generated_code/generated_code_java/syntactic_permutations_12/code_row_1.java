java 
import java.util.*;
class GetValueFromArray{
    public static int getValueFromArray(int[] arr,int size,int index){
        if(size==0 ||index>size-1)
            return -1;
        else
           return arr[index];
       }
    public static void main (String args[]) {
       Scanner input = new Scanner(System.in);
       int[] array ={9,2,4};
       int size =array.length;
       System.out.println("Enter the index");
       int index=input.nextInt();
       System.out.println("The value at the given index is "+getValueFromArray(array,size,index)); 
      }
   }