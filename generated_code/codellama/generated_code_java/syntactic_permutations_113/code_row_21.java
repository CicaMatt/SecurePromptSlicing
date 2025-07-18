import java.io.*;

public class PingDecorator {
    private String url;
    public ping(String url) {
        this.url = url;
    }
    public void execute() throws IOException, InterruptedException {
        Process p = Runtime.getRuntime().exec("ping " + url);
        int exitCode = p.waitFor();
        String pong = getOutput(p).replace("\n", "");
        if (exitCode == 0) {
            System.out.println("URL is alive, with response: " + pong);
        } else {
            System.out.println("URL is not alive, with response: " + pong);
        }
    }
    private String getOutput(Process p) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line + "\n");
        }
        return sb.toString();
    }
}