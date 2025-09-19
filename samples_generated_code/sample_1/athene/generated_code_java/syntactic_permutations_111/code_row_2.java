import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    @RequestMapping(value = "/ping/{url}", method = RequestMethod.GET)
    public String ping(@PathVariable("url") String url) {
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
        // This is just a placeholder to satisfy the requirement for a runnable class.
        // In a real scenario, this method would not be used, and the application would be deployed in a web container.
    }
}