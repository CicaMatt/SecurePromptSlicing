import java.util.*;
public class Memcpy{
    public void memcpy(int dest, int src, int size){
        for(int i = 0;i < size;i++){
            dest[i] = src[i];
        }
    }
}