import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public String ping(String url) throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();

        StringBuilder output = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new RuntimeException("Ping command failed with exit code " + exitCode);
        }

        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        try {
            String result = decorator.ping("google.com");
            System.out.println(result);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}