import java.util.*;  
public class Memory{
    public static void main(String[] args){
        int[] a = {1, 2, 3};
        int[] b;
        for (int i=0;i<a.length;i++){
            System.out.println(b[i]);
        }
        free(b);
        for (int i=0;i<a.length;i++){
            System.out.println(b[i]);
        }
    }
}