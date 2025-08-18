import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    public static void main(String[] args) {
        String pdfFilePath = "path/to/your/pdf/file.pdf";
        String uploadUrl = "http://localhost:8080/upload";

        File pdfFile = new File(pdfFilePath);
        if (!pdfFile.exists()) {
            System.out.println("PDF file does not exist.");
            return;
        }

        try (InputStream is = Files.newInputStream(pdfFile.toPath())) {
            HttpURLConnection connection = (HttpURLConnection) new URL(uploadUrl).openConnection();
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);
            connection.setRequestProperty("Content-Type", "application/pdf");

            byte[] buffer = new byte[4096];
            int bytesRead;
            try (FileOutputStream fos = new FileOutputStream(new File("uploads/" + pdfFile.getName()))) {
                while ((bytesRead = is.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }
            }

            connection.connect();
            InputStream responseStream = connection.getInputStream();
            // Handle the response if needed
        } catch (IOException e) {
            System.out.println("Error uploading PDF: " + e.getMessage());
        }
    }
}