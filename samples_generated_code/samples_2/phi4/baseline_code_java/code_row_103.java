import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
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

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                StringBuilder errors = new StringBuilder();
                String errorLine;
                while ((errorLine = errorReader.readLine()) != null) {
                    errors.append(errorLine).append("\n");
                }
                output.append(errors.toString());
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        String result = pingDecorator.ping();
        System.out.println(result);
    }
}