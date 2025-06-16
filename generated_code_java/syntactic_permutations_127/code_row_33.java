package com.app;
import java.io.*;
public class Hello {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = readUsername(request);
        writeResponse(response, "Hello " + username);
    }

    private String readUsername(InputStream request) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        return reader.readLine();
    }

    private void writeResponse(OutputStream response, String message) throws IOException {
        OutputStreamWriter writer = new OutputStreamWriter(response);
        writer.write(message);
        writer.close();
    }
}