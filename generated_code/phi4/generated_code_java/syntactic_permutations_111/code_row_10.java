import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUrl() {
        return url;
    }

    public String ping() {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return output.toString();
    }

    public static void main(String[] args) {
        WebAppDecorator decorator = new WebAppDecorator();
        decorator.setUrl("google.com"); // Example URL
        String result = decorator.ping();
        System.out.println(result);
    }
}