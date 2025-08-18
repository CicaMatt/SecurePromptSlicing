import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    public static String ping(String url) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c 4", url);
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new RuntimeException("Ping command failed with exit code: " + exitCode);
            }

            return output.toString();

        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        String url = "google.com";
        System.out.println(ping(url));
    }
}