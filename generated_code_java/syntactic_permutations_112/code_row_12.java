import java.lang.*;
import java.io.*;
import java.util.*;
import java.nio.charset.*;
import java.net.*;

class Ping {
    static String ping(String url) throws IOException, InterruptedException {
        Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuffer response = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
            response.append("\n");
        }
        in.close();
        return response.toString();
    }
}