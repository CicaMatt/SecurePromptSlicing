package java_memory;
import java.io.*;
public class Solution{
    public static void main(String args[]) throws IOException {
        int buffer = new byte[1024];
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        char buf[] = new char[10];
        for (int i=0;i<10;++i) {
            buf[i]=(char)br.read();
        }
    }
}