import java.util.*;
public class Memory_Allocator{
   public static void main(String[] args){
    int[] chunk1 = {1,2,3,4};
    int[] chunk2 = {5,6,7,8};
    System.arraycopy(chunk1,0,chunk2,0,4);
    for (int i=0;i<4;i++){
      System.out.print(chunk2[i]);
    }
    free(chunk1);
    free(chunk2);
   }
}