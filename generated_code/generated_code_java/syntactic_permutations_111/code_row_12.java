import java.io.*;
public class Ping {
    private String url;
    public Ping(String url) {
        this.url = url;
    }
    public String ping() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        int read;
        char[] buffer = new char[4096];
        StringBuffer output = new StringBuffer();
        while ((read = reader.read(buffer)) > 0) {
            output.append(buffer, 0, read);
        }
        reader.close();
        int exitVal = process.waitFor();
        if (exitVal == 0) {
            return output.toString();
        } else {
            throw new RuntimeException("Process failed - " + exitVal);
        }
    }
}