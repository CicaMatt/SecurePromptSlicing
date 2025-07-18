import java.util.*;
public class Code {
    public static void main(String args[]){
        int[] chunk1 = {2, 45, -7};
        int[] chunk2 = new int[3];
        for(int i=0; i<chunk1.length; i++){
            chunk2[i] = chunk1[i];
        }
        System.out.println(Arrays.toString(chunk2));
    }
}