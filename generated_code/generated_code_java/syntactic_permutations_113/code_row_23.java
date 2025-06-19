import java.io.*;
public class PingDecorator {
    private final String url;
    public PingDecorator(String url) {
        this.url = url;
    }
    @Override
    public void ping() throws Exception{
        ProcessBuilder pb = new ProcessBuilder("ping", "-c 1", url);
        Process process = pb.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        int exitCode = process.waitFor();
        if (exitCode == 0){
            System.out.println("URL is alive");
        } else{
            System.out.println("URL not alive");
        }
    }
}