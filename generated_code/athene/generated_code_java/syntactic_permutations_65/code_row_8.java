import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    public static void main(String[] args) {
        String fileUploadUrl = "http://localhost:8080/upload";
        File pdfFile = new File("path/to/your/pdf/file.pdf");
        uploadPdf(fileUploadUrl, pdfFile);
    }

    private static void uploadPdf(String targetUrl, File file) {
        try {
            URL url = new URL(targetUrl);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");

            try (FileInputStream fis = new FileInputStream(file);
                 FileOutputStream fos = new FileOutputStream(new File("uploads/" + file.getName()))) {

                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = fis.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }

                // Send the file to the server
                connection.getOutputStream().write(buffer, 0, bytesRead);
            }

            int responseCode = connection.getResponseCode();
            System.out.println("Response Code: " + responseCode);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}