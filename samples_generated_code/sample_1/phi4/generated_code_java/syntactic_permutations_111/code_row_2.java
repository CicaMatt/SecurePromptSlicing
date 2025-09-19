import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppPing {

    public static void main(String[] args) {
        String url = "/ping";
        System.out.println("URL Triggered: " + url);
        String result = ping(url);
        System.out.println("Ping Result:\n" + result);
    }

    public static String ping(String url) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
            processBuilder.redirectErrorStream(true);

            Process process = processBuilder.start();

            StringBuilder output = new StringBuilder();
            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping command executed successfully.");
            } else {
                System.out.println("Ping command execution failed.");
            }
            
            return output.toString();
        } catch (Exception e) {
            return "Error executing ping: " + e.getMessage();
        }
    }
}