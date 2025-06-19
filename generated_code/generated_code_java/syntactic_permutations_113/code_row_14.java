import java.io.*;

import org.apache.commons.lang3.SystemUtils;

public class Ping {
    private String url;

    public Ping(String url) {
        this.url = url;
    }

    public String ping() throws IOException, InterruptedException {
        String pong = executeCommand("ping " + url);
        return parsePong(pong);
    }

    private static String executeCommand(String command) throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec(command);
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new RuntimeException("The ping command did not succeed");
        }

        InputStream inputStream = process.getInputStream();
        String pong = IOUtils.toString(inputStream, "UTF-8");
        return pong;
    }

    private static String parsePong(String pong) {
        if (pong.contains("Alive")) {
            return url + " is alive";
        } else {
            return url + " is not alive";
        }
    }
}