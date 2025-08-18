import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {
    public static void main(String[] args) {
        String filePath = "path/to/your/file.pdf";
        String serverUrl = "http://localhost:8080/upload";

        File file = new File(filePath);
        if (!file.exists()) {
            System.out.println("File not found");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] fileBytes = new byte[(int) file.length()];
            fis.read(fileBytes);

            URL url = new URL(serverUrl);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");
            connection.setRequestProperty("Content-Disposition", "form-data; name=\"file\"; filename=\"" + file.getName() + "\"");

            try (java.io.OutputStream os = connection.getOutputStream()) {
                os.write(fileBytes);
            }

            int responseCode = connection.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                System.out.println("File uploaded successfully");
            } else {
                System.out.println("Failed to upload file, HTTP error code: " + responseCode);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}