import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com";

    public static void main(String[] args) {
        new PingDecorator().run();
    }

    public void run() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url.replace("http://", "").split("/")[0]);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("<br>");
            }
            System.out.println(output.toString());
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}