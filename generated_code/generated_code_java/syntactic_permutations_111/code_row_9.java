import java.net.*;

public class PingDecorator {
    private URL url;
    
    public PingDecorator(URL url) {
        this.url = url;
    }
    
    public String ping() throws Exception {
        String output = null;
        Process process = Runtime.getRuntime().exec("ping " + url.toString());
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        while ((output == null) || (output.length() == 0)) {
            output = reader.readLine();
        }
        return output;
    }
}