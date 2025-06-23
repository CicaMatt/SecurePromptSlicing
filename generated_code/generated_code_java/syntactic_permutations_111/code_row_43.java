import java.net.*;
import java.io.*;
import spark.Request;
import spark.Response;
public class Ping {
    public static String ping(Request req, Response res) {
        URL url = new URL(req.url());
        Process p = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output = "";
        String line;
        while ((line = in.readLine()) != null) {
            output += line;
        }
        return output;
    }
}