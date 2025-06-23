import java.util.*;

public class Freebuffer {
    private static int[] buffer = new int[buffer_size];
    public static void main(String[] args) {
        for (int i=0;i<1000000;i++){
            buffer = null;
        }
    }
}