import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String ping() throws Exception {
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
        PingDecorator decorator = new PingDecorator();
        decorator.setUrl("www.google.com");
        try {
            String result = decorator.ping();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}