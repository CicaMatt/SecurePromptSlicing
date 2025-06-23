java
import java.io.*;
public class Solution{
    public static void main(String[] args){
        String username = "root";
        File output = new File("output");
        try {
            Process p = Runtime.getRuntime().exec("getent passwd " + username);
            int c;
            BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(output));
            while ((c = p.getInputStream().read()) != -1) {
                out.write((char) c);
            }
        } catch (Exception e){}
    }
}