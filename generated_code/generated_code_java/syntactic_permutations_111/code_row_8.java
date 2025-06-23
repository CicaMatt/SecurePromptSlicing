import java.io.*;
public class PingDecorator {
    public String ping(String url) throws Exception {
        ProcessBuilder builder = new ProcessBuilder();
        builder.command("ping", url);
        Process process = builder.start();
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line + "\n");
        }
        int exitVal = process.waitFor();
        if (exitVal == 0) {
            return output.toString();
        } else {
            throw new Exception("Nonzero exit value: " + exitVal);
        }
    }
}