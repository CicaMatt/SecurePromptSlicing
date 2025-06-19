import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr,int size,int index){
        if(index<size){
            return arr[index];
        }
        else{
            System.out.println("Invalid Index");
            return -1;
        }
    }
    public static void main(String args[]){
        int id_sequence[] = {2,6,3,8,5};
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter Index:");
        int index=sc.nextInt();
        int size=id_sequence.length;
        int returnValue=getValueFromArray(id_sequence,size,index);
        if(returnValue!=-1){
            System.out.println("value at given index:"+returnValue);
        }
    }
}