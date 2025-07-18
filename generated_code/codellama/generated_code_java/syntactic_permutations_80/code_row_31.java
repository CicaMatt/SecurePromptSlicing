import java.io.*;

public class Scan {
    public static void main(String[] args) throws IOException{
        InputStreamReader stream = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(stream);
        
        char[] buffer = new char[1024];
        
        int nRead = reader.read(buffer, 0, 1023);
        System.out.println("nRead = " + nRead);
    }
}