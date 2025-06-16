import java.util.*;

class Memmove{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size = 10; //size of memory chunk
        
        int[] firstChunk = new int[size]; //allocates the first chunk
        for (int i=0;i<size;i++)
            firstChunk[i] = sc.nextInt();
        
        int[] secondChunk = new int[size]; //allocates the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size); // copies the contents of the first chunk into the second chunk
        
        firstChunk = null; //frees the first chunk
        
        System.gc(); //run garbage collector to free memory allocated by firstChunk
        
        for (int i=0;i<size;i++)
            secondChunk[i] = sc.nextInt();
        
        System.out.println("Contents of second chunk: ");
        for(int i=0;i<size;i++){
            System.out.print(secondChunk[i]+" ");
        }
    }
}