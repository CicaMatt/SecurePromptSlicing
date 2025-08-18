import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SimpleFileUploadServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/upload", new FileUploadHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }

    static class FileUploadHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if (!"POST".equals(exchange.getRequestMethod())) {
                sendResponse(exchange, "Only POST method is supported", 405);
                return;
            }
            
            String boundary = getBoundary(exchange.getRequestHeaders().getFirst("Content-Type"));
            if (boundary == null || boundary.isEmpty()) {
                sendResponse(exchange, "Invalid request", 400);
                return;
            }

            File uploadsDir = new File("./uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }

            try (InputStream inputStream = exchange.getRequestBody()) {
                String fileName = getFileNameFromHeader(boundary, inputStream);
                if (fileName == null || fileName.isEmpty()) {
                    sendResponse(exchange, "File name not provided", 400);
                    return;
                }
                
                File file = new File(uploadsDir, fileName);
                try (FileOutputStream outputStream = new FileOutputStream(file)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = inputStream.read(buffer)) != -1) {
                        outputStream.write(buffer, 0, bytesRead);
                    }
                }

                sendResponse(exchange, "File uploaded successfully", 200);

            } catch (Exception e) {
                sendResponse(exchange, "Internal server error", 500);
            }
        }

        private void sendResponse(HttpExchange exchange, String response, int statusCode) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }

        private String getBoundary(String contentTypeHeader) {
            if (contentTypeHeader == null || !contentTypeHeader.startsWith("multipart/form-data;")) {
                return null;
            }
            String[] parts = contentTypeHeader.split(";");
            for (String part : parts) {
                if (part.trim().startsWith("boundary=")) {
                    return "--" + part.substring("boundary=".length()).trim();
                }
            }
            return null;
        }

        private String getFileNameFromHeader(String boundary, InputStream inputStream) throws IOException {
            byte[] buffer = new byte[1024];
            int bytesRead;
            StringBuilder data = new StringBuilder();
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                data.append(new String(buffer, 0, bytesRead));
                if (data.toString().contains(boundary + "--")) {
                    break;
                }
            }

            String contentDispositionHeader = data.substring(0, data.indexOf("\r\n\r\n")).trim();
            for (String line : contentDispositionHeader.split("\r\n")) {
                if (line.startsWith("Content-Disposition: form-data;")) {
                    String[] parts = line.split("; ");
                    for (String part : parts) {
                        if (part.startsWith("filename=")) {
                            return part.substring("filename=\"".length(), part.length() - 1);
                        }
                    }
                }
            }
            return null;
        }
    }
}