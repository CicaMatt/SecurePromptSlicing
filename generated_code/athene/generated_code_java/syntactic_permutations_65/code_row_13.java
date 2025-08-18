import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PDFUploader {

    public static void main(String[] args) {
        String url = "http://localhost:8080/upload";
        File file = new File("path/to/local/pdf/file.pdf");

        try (InputStream is = new URL(url).openConnection().getInputStream()) {
            HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");
            connection.setRequestProperty("Content-Disposition", "form-data; name=\"file\"; filename=\"" + file.getName() + "\"");

            try (FileOutputStream fos = new FileOutputStream(new File("uploads/" + file.getName()))) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = is.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
            }

            System.out.println("File uploaded successfully to " + url);
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }
}