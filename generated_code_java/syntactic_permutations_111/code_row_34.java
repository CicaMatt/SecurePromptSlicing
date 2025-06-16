import java.io.*;
import java.util.*;

public class Ping {
    public String ping(String url) throws IOException {
        Process p = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuffer output = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            output.append(inputLine + "\n");
        }
        in.close();
        return output.toString();
    }
}