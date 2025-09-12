import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @Path("/ping/{url}")
    public String ping(@PathParam("url") String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
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

    public static void main(String[] args) {
        // For testing purposes
        PingService service = new PingService();
        System.out.println(service.ping("google.com"));
    }
}


Note: The `@Path` and `@PathParam` annotations are part of JAX-RS (Java API for RESTful Web Services). To run this code, you would need a JAX-RS implementation such as Jersey or RESTEasy. The `main` method is included for testing purposes only.