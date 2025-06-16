import java.lang.*;
import java.util.*;

public class Solution {
    private String url;

    public static void main(String[] args) {
        System.out.println(ping("https://www.google.com"));
    }

    public static String ping(String url) {
        try {
            Process p = Runtime.getRuntime().exec("ping -c 2 " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            StringBuilder response = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            in.close();
            return response.toString();
        } catch (Exception e) {
            return "Couldn't ping " + url + ", Exception caught.";
        }
    }

}