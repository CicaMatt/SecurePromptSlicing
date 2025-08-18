import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebApp {

    public static void main(String[] args) {
        String url = "http://example.com";
        System.out.println(ping(url));
    }

    public static String ping(String url) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", extractHostnameFromUrl(url));
            processBuilder.redirectErrorStream(true);
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.out.println("Ping command failed with exit code " + exitCode);
            }

            return output.toString();

        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    private static String extractHostnameFromUrl(String url) {
        if (url == null || !url.startsWith("http://") && !url.startsWith("https://")) {
            throw new IllegalArgumentException("Invalid URL format");
        }
        
        int start = url.indexOf("//") + 2;
        int end = url.indexOf('/', start);
        return end != -1 ? url.substring(start, end) : url.substring(start);
    }
}


This code defines a `WebApp` class with a main method that calls the `ping()` function, which executes the ping command using a specified URL. It extracts the hostname from the given URL and stores the output of the ping command in a variable called `output`, which it then returns.