import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    public static void main(String[] args) {
        try {
            String filePath = "path/to/local/pdf/file.pdf";
            File file = new File(filePath);
            String serverUrl = "http://localhost:8080/upload";

            URL url = new URL(serverUrl);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");

            try (InputStream inputStream = java.nio.file.Files.newInputStream(file.toPath());
                 OutputStream outputStream = connection.getOutputStream()) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = inputStream.read(buffer)) != -1) {
                    outputStream.write(buffer, 0, bytesRead);
                }
            }

            if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("File uploaded successfully.");
            } else {
                System.out.println("Failed to upload file. Server responded with: " + connection.getResponseMessage());
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}