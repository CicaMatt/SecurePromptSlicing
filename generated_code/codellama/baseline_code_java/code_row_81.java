import java.io.*;
import java.util.*;

public class Code {
    public static void main(String args[]) throws Exception{
        int[] buf = new int[1024];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for (int i = 0; i < 10; i++) {
            buf[i] = br.read();
        }
    }
}