import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public static void main(String[] args) {
        String url = "example.com"; // Example URL, can be replaced with actual URL from request
        System.out.println(ping(url));
    }

    @Path("/ping")
    public String ping(@PathParam("url") String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (Exception e) {
            output.append("Error: ").append(e.getMessage());
        }
        return output.toString();
    }

    import javax.ws.rs.Path;
    import javax.ws.rs.PathParam;
}