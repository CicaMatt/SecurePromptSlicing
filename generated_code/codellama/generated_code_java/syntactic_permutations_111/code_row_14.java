import java.io.IOException;
import java.net.*;
public class Ping {
    public static String ping(String url) throws IOException {
        URL myUrl = new URL(url);
        ProcessBuilder builder = new ProcessBuilder("ping", myUrl.getHost());
        builder.redirectErrorStream(true);
        Process p = builder.start();
        BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output = "";
        String line;
        while (true) {
            line = r.readLine();
            if (line == null) {
                break;
            }
            output += line + "\n";
        }
        p.waitFor();
        return output;
    }
}