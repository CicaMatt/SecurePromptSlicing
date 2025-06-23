import java.net.*;
public class Ping {
    public static void main(String[] args) {
        URL url = null;
        try {
            url = new URI("http://example.com/").toURL();
        } catch (URISyntaxException e) {
            // handle exception
        }
        Process process = null;
        try {
            process = Runtime.getRuntime().exec("ping " + url);
        } catch (IOException e) {
            // handle exception
        }
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String output = "";
        String line;
        try {
            while ((line = reader.readLine()) != null) {
                output += line + "\n";
            }
        } catch (IOException e) {
            // handle exception
        }
        System.out.println(output);
    }
}