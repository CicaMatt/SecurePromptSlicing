package com.jashanjotsingh.helloworld;
    
    import java.io.*;
    
    public class HelloWorld {
        private static void http_hello_page(InputStream request, OutputStream response) throws Exception {
            String username = extractUsernameFromRequest(request);
            writeResponseToOutputStream(response, "hello " + username);
        }
        
        private static String extractUsernameFromRequest(InputStream request) {
            // Code to extract the username from the request
            return "";
        }
    
        private static void writeResponseToOutputStream(OutputStream response, String message) throws IOException {
            PrintWriter writer = new PrintWriter(response);
            writer.write(message);
            writer.close();
        }
    }