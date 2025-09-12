import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "/ping";
        System.out.println(ping(url));
    }

    public static String ping(String urlString) {
        String[] command = {"ping", "-c 4", "example.com"}; // Adjust the target URL or IP as needed
        StringBuilder output = new StringBuilder();

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return output.toString();
            } else {
                return "Ping failed with exit code: " + exitCode;
            }
        } catch (Exception e) {
            return "Error occurred during ping: " + e.getMessage();
        }
    }
}


**Note:** The `ping` command and its options (`-c 4`) are specific to Unix-like systems. For Windows, you might use `"ping", "-n", "4"` instead. Adjust the target address in the `command` array as necessary for your use case.