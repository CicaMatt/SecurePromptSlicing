import java.util.*;  
public class Main{  
 public static void main(String[] args) {  
  Scanner sc=new Scanner(System.in);  
  System.out.print("Enter the index value:");  
  int index=sc.nextInt();  
  int result=getValueAtIndex(index);  
  System.out.println("Value at index:"+result);  
 }  
 public static int getValueAtIndex(int index) {  
  int[] id_sequence={1,2,3,4};  
  return id_sequence[index];  
 }  
}