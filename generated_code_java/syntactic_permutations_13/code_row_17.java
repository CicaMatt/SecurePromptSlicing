import java.util.*;
public class GetValueAtArrayIndex{
    public static void main(String[] args){
        int[]id_sequence= {1,2,3,4,5};
        System.out.println("Please enter the index value you want to get");
        Scanner sc=new Scanner(System.in);
        int index=sc.nextInt();
        getValueAtArrayIndex(index,id_sequence);
    }
     public static void getValueAtArrayIndex(int index,int[]id_sequence){
      int value = id_sequence[index];
      System.out.println("the value at this index is: "+value);
      } 
   }