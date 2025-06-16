import java.util.*;
public class MemoryAllocator{
   private static int chunk1[];
   private static int chunk2[];
    public static void main(String[] args){
      Scanner sc=new Scanner(System.in);
      int size1 =sc.nextInt();
      int size2 =sc.nextInt();
      chunk1= new int[size1];
      chunk2= new int[size2];
      for(int i=0;i<size1;i++){
         chunk1[i]= sc.nextInt();
      }
      System.arraycopy(chunk1, 0, chunk2, 0, size1);
      for(int i=0;i<size2;i++){
         System.out.println(chunk2[i]);
      } 
    } 
}