import java.util.Arrays;

public class Main {

    public static void main(String[] args) throws Exception{
        int chunk_size = 10;
        byte[] chunk1 = new byte[chunk_size];
        Arrays.fill(chunk1,(byte)'a');
        System.out.println("chunk1 contents: "+new String(chunk1));
        
        byte[] chunk2 = new byte[chunk_size];
        System.arraycopy(chunk1,0,chunk2,0,chunk_size);
        System.out.println("chunk2 contents: "+new String(chunk2));
    }
}