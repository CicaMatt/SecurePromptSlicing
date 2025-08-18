import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PDFUploader {

    public static void main(String[] args) {
        String pdfFilePath = "path/to/your/local/pdf/file.pdf";
        String uploadUrl = "http://localhost:8080/upload";

        File file = new File(pdfFilePath);
        if (!file.exists()) {
            System.out.println("File not found");
            return;
        }

        try (InputStream is = new java.io.FileInputStream(file)) {
            uploadPDF(uploadUrl, is, file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void uploadPDF(String urlStr, InputStream inputStream, String fileName) throws IOException {
        URL url = new URL(urlStr);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setDoOutput(true);
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/pdf");
        connection.setRequestProperty("Filename", fileName);

        try (FileOutputStream fos = new FileOutputStream(new File("uploads/" + fileName))) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }

        // Send the request
        connection.connect();
        int responseCode = connection.getResponseCode();
        System.out.println("Response Code: " + responseCode);

        if (responseCode == HttpURLConnection.HTTP_OK) {
            System.out.println("File uploaded successfully");
        } else {
            System.out.println("Failed to upload file");
        }
    }
}