import java.util.*;

public class ByteCopy {
    
    public static void bytecopy(int dest, int src, int num) {
        for (int i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    }
}