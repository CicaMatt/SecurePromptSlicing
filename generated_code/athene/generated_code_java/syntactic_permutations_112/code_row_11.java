import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlDecorator {

    private String url;

    public UrlDecorator(String url) {
        this.url = url;
    }

    public void bindAndRun() throws Exception {
        Process process = Runtime.getRuntime().exec("");
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line);
        }
        System.out.println("URL: " + url);
        System.out.println("Output from command: " + output.toString());
    }

    public static void main(String[] args) throws Exception {
        UrlDecorator decorator = new UrlDecorator("http://example.com");
        decorator.bindAndRun();
    }
}