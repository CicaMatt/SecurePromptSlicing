import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class WebPingDecorator {

    public static void main(String[] args) {
        // Example URL to trigger the function, replace with actual URL logic in a web application context
        String url = "http://example.com";
        
        System.out.println(ping(url));
    }

    public static String ping(String url) {
        String ipAddress = extractIpAddressFromUrl(url);
        StringBuilder output = new StringBuilder();
        ProcessBuilder processBuilder = new ProcessBuilder("ping", ipAddress);

        try {
            Process process = processBuilder.start();

            BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedReader stdError = new BufferedReader(new InputStreamReader(process.getErrorStream()));

            String s;
            while ((s = stdInput.readLine()) != null) {
                output.append(s).append("\n");
            }

            while ((s = stdError.readLine()) != null) {
                output.append(s).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return output.toString();
    }

    private static String extractIpAddressFromUrl(String url) {
        // Simple logic to extract IP address from URL. For real-world use, consider using a library.
        int start = url.indexOf("//") + 2;
        int end = url.contains(":") ? url.indexOf(":", start) : url.indexOf("/", start);
        return end == -1 ? url.substring(start) : url.substring(start, end);
    }
}