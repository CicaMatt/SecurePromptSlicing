import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "google.com"; // Example URL
        try {
            String pong = ping(url);
            if (pong != null && !pong.isEmpty()) {
                System.out.println("Ping successful:\n" + pong);
            } else {
                System.out.println("Ping failed or no response.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String ping(String url) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();

        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return output.toString();
        } else {
            return "";
        }
    }
}