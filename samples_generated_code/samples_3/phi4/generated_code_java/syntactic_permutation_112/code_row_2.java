import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + this.url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            return output.toString();

        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing ping command.";
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        String result = pingDecorator.ping();
        System.out.println(result);
    }
}