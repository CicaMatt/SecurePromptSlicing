import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().run();
    }

    public void run() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}