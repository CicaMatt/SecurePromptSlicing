import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().bindAndRun();
    }

    public void bindAndRun() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url.replace("http://", "").replace("/", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor();
            System.out.println(output.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}