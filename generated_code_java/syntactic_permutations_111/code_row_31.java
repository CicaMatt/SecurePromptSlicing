import java.io.*;

public class PingDecorator implements WebFunction {
    @Override
    public String execute(String url) {
        ProcessBuilder builder = new ProcessBuilder("ping", url);
        builder.redirectErrorStream(true);
        Process process;
        try {
            process = builder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String output = reader.lines().collect(Collectors.joining("\n"));
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "SUCCESS";
            } else {
                return "FAILURE";
            }
        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}