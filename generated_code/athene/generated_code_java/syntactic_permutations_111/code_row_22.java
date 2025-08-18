import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingServlet {

    public String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        PingServlet servlet = new PingServlet();
        String url = args.length > 0 ? args[0] : "google.com";
        System.out.println(servlet.ping(url));
    }
}