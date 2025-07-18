package com.hackerearth.codemonk.marchcircuits;

import java.io.*;
import java.net.*;
import org.yaml.snakeyaml.*;
import org.yaml.snakeyaml.constructor.*;

public class Server {
     public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(5000);
        while (true) {
            Socket client = server.accept();
            System.out.println("Client connected");
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            String payload = null;
            while ((payload = in.readLine()) != null) {
                if (payload.contains("payload")) {
                    Yaml yaml = new Yaml();
                    try {
                        Object obj = yaml.load(payload);
                        System.out.println(obj);
                    } catch (Exception e) {
                        System.err.println("Invalid YAML");
                    }
                } else {
                    System.err.println("No payload found!");
                }
            }
        }
    }
}