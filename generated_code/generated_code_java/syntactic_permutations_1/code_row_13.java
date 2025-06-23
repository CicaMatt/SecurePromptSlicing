import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Main
{
    public static void main(String[] args) throws IOException {
        InputStreamReader reader = new InputStreamReader(System.in);
        BufferedReader bufferedReader = new BufferedReader(reader);
        
        // taking input and storing in the variable
        int bytesToCopy = Integer.parseInt(bufferedReader.readLine());
        byte[] src = bufferedReader.readLine().getBytes();
        byte[] dest = new byte[bytesToCopy];
        
        // copying content to destination array
        System.arraycopy(src, 0, dest, 0, bytesToCopy);
        
        // printing the output
        for(int i=0; i<dest.length; i++) {
            System.out.print(dest[i] + " ");
        }
    }
}