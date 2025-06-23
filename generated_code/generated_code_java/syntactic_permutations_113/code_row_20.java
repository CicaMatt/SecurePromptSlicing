import java.io.*;
import java.util.*;

public class Ping {
    private String url;
    public void ping(String url) throws IOException, InterruptedException {
        ProcessBuilder process = new ProcessBuilder();
        List<String> command = new ArrayList<>();
        command.add("ping");
        command.add(url);
        process.command(command);
        Process p;
        int status;
        p = process.start();
        status = p.waitFor();
        String pong = "URL is alive";
        if (status != 0) {
            pong = "URL is not alive";
        }
        System.out.println(pong);
    }
}