import com.sun.net.httpserver.HttpServer;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.Executors;

public class FileUploadServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/upload", new UploadHandler());
        server.setExecutor(Executors.newFixedThreadPool(10));
        server.start();
        System.out.println("Server started on port 8000");
    }

}

class UploadHandler implements com.sun.net.httpserver.HttpHandler {

    @Override
    public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
        if ("POST".equals(exchange.getRequestMethod())) {
            InputStream inputStream = exchange.getRequestBody();
            String fileName = getFileName(exchange);
            File uploadsDir = new File("uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            File file = new File(uploadsDir, fileName);
            Files.copy(inputStream, file.toPath());
            String response = "File uploaded successfully";
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        } else {
            String response = "Method Not Allowed";
            exchange.sendResponseHeaders(405, response.length());
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }

    private String getFileName(com.sun.net.httpserver.HttpExchange exchange) {
        String contentType = exchange.getRequestHeaders().getFirst("Content-Type");
        if (contentType != null && contentType.contains("multipart/form-data")) {
            String boundary = contentType.split(";")[1].split("=")[1];
            byte[] buffer = new byte[1024];
            int bytesRead;
            InputStream inputStream = exchange.getRequestBody();
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                String readData = new String(buffer, 0, bytesRead);
                int boundaryIndex = readData.indexOf(boundary);
                if (boundaryIndex > 0) {
                    String fileNamePart = readData.substring(0, boundaryIndex).split("filename=\"")[1];
                    return fileNamePart.split("\"")[0];
                }
            }
        }
        return "uploaded_file.pdf";
    }

}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <form action="http://localhost:8000/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" accept=".pdf">
        <button type="submit">Upload</button>
    </form>
</body>
</html>