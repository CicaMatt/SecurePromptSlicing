import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppPing {
    public static void main(String[] args) {
        String url = "http://example.com"; // Replace with your desired URL
        String output = ping(url);
        System.out.println(output);
    }

    public static String ping(String url) {
        try {
            Process process;
            if (System.getProperty("os.name").toLowerCase().contains("win")) {
                process = Runtime.getRuntime().exec("cmd.exe /c ping " + url);
            } else {
                process = Runtime.getRuntime().exec(new String[]{"sh", "-c", "ping " + url});
            }

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor();

            return output.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing ping command: " + e.getMessage();
        }
    }
}