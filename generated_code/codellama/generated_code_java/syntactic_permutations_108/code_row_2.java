import java.io.*;
public class Solution{
    public static void main(String[] args) throws IOException {
        String username = args[0];
        Process p = Runtime.getRuntime().exec("getent passwd " + username);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}