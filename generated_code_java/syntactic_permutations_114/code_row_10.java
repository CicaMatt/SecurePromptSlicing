import java.io.IOException;
import java.util.*;
public class Solution {
    public static void main(String[] args) throws IOException {
        String output = "";
        Process p = Runtime.getRuntime().exec("ls -l");
        BufferedReader inputStream = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = inputStream.readLine()) != null) {
            output += line;
        }
        System.out.println(output);
    }
}