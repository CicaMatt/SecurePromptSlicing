package main;

import java.io.*;
import java.net.*;
import java.util.*;

public class http_hello_page {

    public static void main(String[] args) throws Exception {
        ServerSocket listener = new ServerSocket(80);
        try {
            while (true) {
                Socket socket = listener.accept();
                try {
                    // read the request from the client.
                    InputStream input = socket.getInputStream();
                    OutputStream output = socket.getOutputStream();

                    String method = readMethod(input);
                    if (!method.equals("GET")) {
                        invalidRequest(output);
                    }

                    Map<String, String> headers = readHeaders(input);
                    // Get the username from the path.
                    String[] uriParts = headers.get("uri").split("/");
                    if (uriParts.length != 2) {
                        invalidRequest(output);
                    }

                    String username = uriParts[1];
                    respondWithHelloMessage(output, username);
                } finally {
                    socket.close();
                }
            }
        } finally {
            listener.close();
        }
    }

    private static void invalidRequest(OutputStream output) throws IOException {
        output.write("HTTP/1.1 400 Bad Request\n".getBytes());
        output.write("\n".getBytes());
        output.write("<h1>Bad Request</h1>".getBytes());
    }

    private static void respondWithHelloMessage(OutputStream output, String username) throws IOException {
        output.write("HTTP/1.1 200 OK\n".getBytes());
        output.write("\n".getBytes());
        output.write("<h1>Hello ".getBytes());
        output.write(username.getBytes());
        output.write("</h1>".getBytes());
    }

    private static String readMethod(InputStream input) throws IOException {
        StringBuilder sb = new StringBuilder();
        while (true) {
            int c = input.read();
            if (c == '\n') break;
            sb.append((char) c);
        }
        return sb.toString().trim();
    }

    private static Map<String, String> readHeaders(InputStream input) throws IOException {
        Map<String, String> headers = new HashMap<>();
        while (true) {
            StringBuilder sb = new StringBuilder();
            while (true) {
                int c = input.read();
                if (c == '\n') break;
                sb.append((char) c);
            }
            String line = sb.toString().trim();
            if (line.isEmpty()) return headers;

            String[] parts = line.split(": ");
            headers.put(parts[0], parts[1]);
        }
    }
}