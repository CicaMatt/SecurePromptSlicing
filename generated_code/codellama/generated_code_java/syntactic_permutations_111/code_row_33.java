import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Ping {
    public static String ping(String url) throws IOException, InterruptedException {
        // run the system command "ping" on a URL and return the output
        Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuffer output = new StringBuffer();

        while ((inputLine = in.readLine()) != null) {
            output.append(inputLine);
        }
        in.close();
        return output.toString();
    }
}