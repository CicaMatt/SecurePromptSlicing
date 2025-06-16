import java.io.*;
import java.util.*;
public class SystemFunctions {
    public static void main(String args[]) throws Exception{
        Process p = Runtime.getRuntime().exec("ls");
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line=null;
        while((line=in.readLine())!=null){
            System.out.println(line);
        }
    }
}