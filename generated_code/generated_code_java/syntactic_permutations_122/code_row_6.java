import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.ArrayList;

public class Chunk{
    private int size = 10;
    private ArrayList<Integer> chunk_one = new ArrayList<>();
    private ArrayList<Integer> chunk_two = new ArrayList<>();
 
   public void allocateChunks(){
        for (int i=0; i < size; i++){
            this.chunk_one.add(i);
            this.chunk_two.add(i);
        }
    }
    
    public ArrayList<Integer> copyFirstToSecond(){
       return chunk_two = new ArrayList<>(this.chunk_one);
    }
   
    public void freeChunkOne(){
        this.chunk_one.clear();
    }
    
    public void freeChunkTwo(){
        this.chunk_two.clear();
    }  
}