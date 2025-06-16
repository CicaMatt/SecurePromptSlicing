import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.lang.*;
 
public class ping {
    public static void main(String[] args) {
        String url = "https://www.google.com";
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
            in.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}