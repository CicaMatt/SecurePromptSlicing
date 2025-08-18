import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "/ping"; // This would be set based on the URL triggering the request in a real web application.
        
        if ("/ping".equals(url)) {
            String output = ping("8.8.8.8"); // Example IP address, replace with dynamic input as needed
            System.out.println(output);
        }
    }

    public static String ping(String ipAddress) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            processBuilder.command("cmd.exe", "/c", "ping -n 4 " + ipAddress); // '-n' for count on Windows
        } else {
            processBuilder.command("bash", "-c", "ping -c 4 " + ipAddress); // '-c' for count on Unix-based systems
        }
        
        StringBuilder output = new StringBuilder();
        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.out.println("Error: Ping command failed.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return output.toString();
    }
}