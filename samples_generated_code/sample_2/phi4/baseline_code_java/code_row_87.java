import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public String getPingResult() throws Exception {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        return output.toString();
    }

    public static void main(String[] args) {
        try {
            PingDecorator pingDecorator = new PingDecorator("example.com"); // Replace "example.com" with the desired URL
            String result = pingDecorator.getPingResult();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}