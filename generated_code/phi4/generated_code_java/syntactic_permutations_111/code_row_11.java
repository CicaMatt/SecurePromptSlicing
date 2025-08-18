import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String getPingOutput() throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();

        if (exitCode == 0) {
            return output.toString();
        } else {
            throw new RuntimeException("Ping command failed with exit code " + exitCode);
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator();
        pingDecorator.setUrl("www.google.com");

        try {
            String result = pingDecorator.getPingOutput();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}