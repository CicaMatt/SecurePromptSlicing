import java.io.*;
import java.util.*;

public class Ping {
    public static String ping(String url) {
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            StringBuilder response = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            in.close();
            return response.toString();
        } catch (Exception e) {
            System.out.println("Error: " + e);
            return "";
        }
    }
}