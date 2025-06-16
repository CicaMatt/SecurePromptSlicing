import java.io.*;
import java.util.*;

public class HelloWorld {
	
    public static void main(String[] args) {
        int x;
        x = (int)readInt();
        x=x+1000;
        System.out.println(x);
    }
    public static double readDouble() throws IOException {
        InputStreamReader r = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(r);
        String line = reader.readLine();
        return Double.parseDouble(line);
    }
    
    public static int readInt() throws IOException {
        InputStreamReader r = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(r);
        String line = reader.readLine();
        return Integer.parseInt(line);
    }
}