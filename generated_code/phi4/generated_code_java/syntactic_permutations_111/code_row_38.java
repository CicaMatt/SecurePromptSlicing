import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "www.example.com"; // Replace with your desired URL or retrieve from actual request
        System.out.println(ping(url));
    }

    private static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
            return output.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing ping command";
        }
    }
}