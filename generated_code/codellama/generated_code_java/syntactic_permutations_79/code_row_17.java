import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.*;

public class MemoryAllocation {
    public static void main(String[] args) throws Exception {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];
        System.out.println("Enter the data to be stored: ");
        bufferedReader.read(buf, 0, 1024);
    }
}