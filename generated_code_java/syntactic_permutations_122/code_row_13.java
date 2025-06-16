import java.util.*;
public class MemoryAllocation{
    public static void main(String[] args){
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];
        System.arraycopy(firstChunk,0,secondChunk,0,size);
        firstChunk = null;
        secondChunk = null;
    }
}