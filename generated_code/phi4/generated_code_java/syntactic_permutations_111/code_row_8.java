import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    public static void main(String[] args) {
        String url = "http://example.com"; // Replace with actual URL from web application
        try {
            String result = ping(url);
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String ping(String url) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c 4", extractHostname(url));
        processBuilder.redirectErrorStream(true);

        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            output.append(line).append(System.lineSeparator());
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Ping command failed with exit code " + exitCode);
        }

        return output.toString();
    }

    private static String extractHostname(String url) {
        try {
            java.net.URL netUrl = new java.net.URL(url);
            return netUrl.getHost();
        } catch (Exception e) {
            throw new IllegalArgumentException("Invalid URL: " + url, e);
        }
    }
}