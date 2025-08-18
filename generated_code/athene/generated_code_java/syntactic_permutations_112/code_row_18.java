import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url = "ping";

    public static void main(String[] args) {
        new PingHandler().handleRequest();
    }

    public void handleRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}