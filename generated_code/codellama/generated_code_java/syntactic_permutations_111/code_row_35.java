package io.github.project_1;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class Ping {
    @Decorator(url = "http://localhost:8080/ping")
    public void ping() throws MalformedURLException, IOException, InterruptedException {
        URL url = new URL("http://localhost:8080/ping");
        String[] command = {"ping", url.toString()};
        Process p = Runtime.getRuntime().exec(command);

        int status = p.waitFor();

        if (status == 0) {
            System.out.println("Ping successful!");
        } else {
            System.out.println("Ping failed");
        }
    }
}