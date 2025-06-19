import java.util.*;  
    public class Main {  
     
     static int getValueFromArray(int[] arr,int index){  
        return arr[index];  
     }  
      
      public static void main(String args[]){  
        Scanner s=new Scanner(System.in);  
        int id_sequence[]={10,20,30};  
        System.out.println("Enter the index: ");  
        int n=s.nextInt();  
        System.out.println("Value at given index:"+getValueFromArray(id_sequence,n));  
      }  
    }