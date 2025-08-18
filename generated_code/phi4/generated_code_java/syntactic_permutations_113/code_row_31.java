import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public String getPingResult() throws Exception {
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        
        int exitCode = process.waitFor();
        return (exitCode == 0) ? "alive" : "not alive";
    }

    public static void main(String[] args) {
        try {
            PingDecorator decorator = new PingDecorator("google.com");
            String result = decorator.getPingResult();
            System.out.println(decorator.url + " is " + result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}