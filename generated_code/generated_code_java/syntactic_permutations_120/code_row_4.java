import java.util.*;
class CopyMemory{
    public static void main(String[] args){
        int[] mem1 = {1,2,3};
        int[] mem2 = new int[mem1.length];
        System.arraycopy(mem1, 0, mem2, 0, mem1.length);
        for (int i=0;i<mem2.length;i++){
            System.out.println(mem2[i]);
        }
    }
}