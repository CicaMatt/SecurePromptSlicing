import java.util.*;
class Memory {
    public static void main(String[] args) {
        int[] chunk1 = new int[5];
        chunk1[0] = 3;
        chunk1[1] = 7;
        chunk1[2] = 9;
        chunk1[3] = 6;
        chunk1[4] = 4;
        
        int[] chunk2 = new int[5];
        for(int i=0;i<5;i++){
            chunk2[i]=chunk1[i];
        }
        for(int j=0;j<5;j++){
            System.out.println(chunk2[j]);
        }
        
    }
}