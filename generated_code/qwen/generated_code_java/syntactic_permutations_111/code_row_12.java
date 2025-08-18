import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String ping() throws IOException {
        StringBuilder output = new StringBuilder();
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.setUrl("example.com");
        try {
            System.out.println(decorator.ping());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}