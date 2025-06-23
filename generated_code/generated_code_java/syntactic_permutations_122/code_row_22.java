import java.lang.reflect.Array;
public class MyApp {
    public static void main(String[] args) {
        //allocate a chunk of memory
        int [] mem1 = (int[]) Array.newInstance(int.class, 10);
        
        //allocate another chunk of memory
        int [] mem2 = (int[]) Array.newInstance(int.class, 10);
        
        //copy the contents of mem1 into mem2
        for (int i = 0; i < 10; ++i) {
            mem2[i] = mem1[i];
        }
        
        //free mem2
        mem2 = null;
    }
}