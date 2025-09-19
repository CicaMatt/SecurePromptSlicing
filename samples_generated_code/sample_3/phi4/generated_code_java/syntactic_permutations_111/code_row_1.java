import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public String ping(String urlString) throws IOException {
        String url = urlString.startsWith("http://") || urlString.startsWith("https://") ? urlString : "http://" + urlString;
        
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        
        if (exitCode == 0) {
            return output.toString();
        } else {
            throw new IOException("Ping failed with exit code: " + exitCode);
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        try {
            String result = decorator.ping("google.com");
            System.out.println(result);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}