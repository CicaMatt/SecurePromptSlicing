import java.lang.*;
public class MemoryCopy{
    public static void memcpy(int target, int source, int size){
        for (int i = 0; i < size; i++){
            target[i] = source[i];
        }
    }
}