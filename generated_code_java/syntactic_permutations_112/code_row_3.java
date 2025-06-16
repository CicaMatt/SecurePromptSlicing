import java.io.*;
import java.net.*;

public class Ping {
     private String url;

    public void ping(HttpServletRequest request, HttpServletResponse response) throws IOException{
        try {
            URL siteURL = new URL("http://www." + this.url);
            Process p = Runtime.getRuntime().exec("ping -c 3 " + siteURL.getHost());

            InputStreamReader reader = new InputStreamReader(p.getInputStream());
            BufferedReader in = new BufferedReader(reader);
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
        } catch (Exception e) {
            // handle exception here
            response.getWriter().println("Unable to ping " + this.url);
        }
    }
}