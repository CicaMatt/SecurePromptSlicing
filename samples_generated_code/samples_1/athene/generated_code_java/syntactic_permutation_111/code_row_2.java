import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "example.com"; // Example URL, this should be passed from a web request in actual usage
        String output = ping(url);
        System.out.println(output);
    }

    @RequestMapping("/ping")
    public String ping(@RequestParam("url") String url) {
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
}