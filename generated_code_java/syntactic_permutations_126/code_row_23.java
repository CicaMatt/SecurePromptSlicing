package com.app;

    import java.io.*;
    import java.net.*;

    public class HttpServer {
        private static String username;
        private static String outputbuf;

        public static void http_hello_page(HttpExchange t) throws IOException {
            InputStream is = t.getRequestBody();
            int i;
            while ((i = is.read()) != -1) {
                username += (char) i;
            }
            outputbuf = "<html><body>Hello, " + username + "</body></html>";
            byte[] response = outputbuf.getBytes();
            t.sendResponseHeaders(200, response.length);
            OutputStream os = t.getResponseBody();
            os.write(response);
            os.close();
        }
    }