import java.util.Arrays;
    
    public class TwoChunks {
        public static void main(String[] args) {
            int[] chunk1 = new int[10];
            Arrays.fill(chunk1, 42);
        
            int[] chunk2 = new int[10];
            System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);
        
            chunk1 = null;
            System.gc();
        
            for (int i : chunk2) {
                System.out.println(i);
            }
        }
    }