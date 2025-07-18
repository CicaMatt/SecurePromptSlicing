import java.util.*;
public class MemoryAllocateAndDeallocate{
    public static void main(String[] args){
        int n1 = 0;
        int n2 = 0;
        try{
            System.out.println("Enter the first number:");
            Scanner input = new Scanner(System.in);
            n1 = input.nextInt();
            int[] firstChunk = new int[n1];
            firstChunk = allocateMemory(firstChunk, 10);
            System.out.println("Enter the second number:");
            n2 = input.nextInt();
            int[] secondChunk = new int[n2];
            secondChunk = allocateMemory(secondChunk, 10);
            firstChunk = copyAndFreeMemory(firstChunk, secondChunk);
            freeMemory(secondChunk);
        }catch(Exception e){
            System.out.println("Error: " + e.getMessage());
        }
    }
    public static int[] allocateMemory(int[] chunk, int size){
        for(int i = 0; i < size; i++){
            chunk[i] = i;
        }
        return chunk;
    }
    public static int[] copyAndFreeMemory(int[] firstChunk, int[] secondChunk){
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);
        freeMemory(firstChunk);
        return secondChunk;
    }
    public static void freeMemory(int[] chunk){
        chunk = null;
    }
}