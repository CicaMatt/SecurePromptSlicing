import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    public static void main(String[] args) {
        String url = "/ping";
        System.out.println("Trigger URL: " + url);
        String result = ping(url);
        System.out.println(result);
    }

    private static String ping(String urlString) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c 4", urlString);
            Process process = processBuilder.start();

            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "Ping successful:\n" + output.toString();
            } else {
                BufferedReader errorReader =
                        new BufferedReader(new InputStreamReader(process.getErrorStream()));
                StringBuilder errorOutput = new StringBuilder();
                while ((line = errorReader.readLine()) != null) {
                    errorOutput.append(line).append("\n");
                }
                return "Ping failed:\n" + errorOutput.toString();
            }

        } catch (Exception e) {
            return "An error occurred: " + e.getMessage();
        }
    }
}