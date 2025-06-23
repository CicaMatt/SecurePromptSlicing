import java.io.*;
 
public class Ping {
    public static String ping(String url) {
        String output = "";
        try{
            Process p = Runtime.getRuntime().exec("ping -c1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = "";
            while ((line = reader.readLine())!= null) {
                output += line;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return output;
    }
}