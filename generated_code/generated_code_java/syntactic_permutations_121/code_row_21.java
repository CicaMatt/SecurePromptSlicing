import java.util.*;
class Code{
    public static void main(String[] args){
        int[] chunkOne = new int[3];
        int[] chunkTwo = new int[3];
        for(int i=0;i<chunkOne.length;i++){
            System.out.println(chunkOne[i]);
        }
        free(chunkOne);
        for(int i=0;i<chunkTwo.length;i++){
            System.out.println(chunkTwo[i]);
        }
        free(chunkTwo);
    }
    public static void free(Object obj){
        if(obj instanceof int[]){
            Arrays.fill((int[]) obj,0);
        }
    }
}