import java.lang.*;
import java.util.*;
class MyProgram {
    public static void main (String[] args) {
        //allocate memory for chunk #1
        byte[] chunk1 = new byte[256];
        //populate data in chunk#1
        for(int i=0;i<chunk1.length;i++){
            chunk1[i]=(byte)(i%128);
        }
        
        //allocate memory for chunk #2
        byte[] chunk2 = new byte[256];
        //copy data from chunk#1 to chunk#2
        for(int i=0;i<chunk1.length;i++){
            chunk2[i]=chunk1[i];
        }
        
        //free memory allocated for chunk#1
        chunk1 = null;
        
        //free memory allocated for chunk#2
        chunk2 = null;
    }
}