package com.example.myapplication;

import java.io.*;
import java.net.*;
import java.util.*;

public class MyApplication {
    public static void main(String[] args) throws Exception {
        ServerSocket socket = new ServerSocket(5000);
        while (true) {
            Socket connectionSocket = socket.accept();
            try {
                BufferedReader in = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                PrintWriter out = new PrintWriter(connectionSocket.getOutputStream(), true);
                String requestString = "";
                while (in.ready()) {
                    requestString += (char) in.read();
                }
                Map<String, List<String>> parameters = parseQueryParameters(requestString);
                if (!parameters.containsKey("payload")) {
                    out.println("HTTP/1.1 400 Bad Request");
                    out.println();
                    out.flush();
                    continue;
                }
                String payload = parameters.get("payload").get(0);
                if (payload.equals("Create")) {
                    out.println("HTTP/1.1 422 Unprocessable Entity");
                    out.println();
                    out.flush();
                    continue;
                }
                out.println("HTTP/1.1 200 OK");
                out.println();
                out.flush();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                connectionSocket.close();
            }
        }
    }

    private static Map<String, List<String>> parseQueryParameters(String requestString) throws UnsupportedEncodingException {
        String query = requestString.split("\\?")[1];
        Map<String, List<String>> parameters = new HashMap<>();
        for (String param : query.split("&")) {
            String name = param.split("=")[0];
            String value = URLDecoder.decode(param.split("=")[1], "UTF-8");
            if (!parameters.containsKey(name)) {
                parameters.put(name, new ArrayList<>());
            }
            parameters.get(name).add(value);
        }
        return parameters;
    }
}