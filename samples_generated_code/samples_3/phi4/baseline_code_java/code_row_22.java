import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlPingDecorator {

    private String url;

    public UrlPingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl() {
        System.out.println("Binding to URL: " + url);
        String pong = ping(url);

        if (pong.contains("0% packet loss")) {
            System.out.println("The URL " + url + " is alive.");
        } else {
            System.out.println("The URL " + url + " is not alive.");
        }
    }

    private String ping(String urlString) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + urlString);
            BufferedReader inputReader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = inputReader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            return "Exit Code: " + exitCode + "\n" + output.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing ping command.";
        }
    }

    public static void main(String[] args) {
        UrlPingDecorator decorator = new UrlPingDecorator("google.com");
        decorator.bindToUrl();
    }
}