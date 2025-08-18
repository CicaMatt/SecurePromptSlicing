import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String url) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c 4", url);
            processBuilder.redirectErrorStream(true);

            Process process = processBuilder.start();
            StringBuilder output = new StringBuilder();

            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()))) {

                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append(System.lineSeparator());
                }
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return output.toString();
            } else {
                return "Ping failed with exit code: " + exitCode;
            }
        } catch (IOException | InterruptedException e) {
            return "Error during ping execution: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        String url = "www.example.com";
        System.out.println(ping(url));
    }
}