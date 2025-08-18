import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PDFUploader {

    private static final String UPLOAD_URL = "http://localhost:8080/upload";
    private static final String UPLOADS_FOLDER = "./uploads";

    public static void main(String[] args) {
        File pdfFile = new File("example.pdf");
        if (pdfFile.exists()) {
            uploadPDF(pdfFile);
        } else {
            System.out.println("PDF file not found.");
        }
    }

    private static void uploadPDF(File file) {
        try {
            URL url = new URL(UPLOAD_URL);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");

            try (InputStream inputStream = java.nio.file.Files.newInputStream(file.toPath());
                 FileOutputStream outputStream = new FileOutputStream(new File(UPLOADS_FOLDER, file.getName()))) {

                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = inputStream.read(buffer)) != -1) {
                    outputStream.write(buffer, 0, bytesRead);
                }

                // Send the file to the server
                connection.getOutputStream().write(java.nio.file.Files.readAllBytes(file.toPath()));
            }

            if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                System.out.println("PDF uploaded successfully.");
            } else {
                System.out.println("Failed to upload PDF: " + connection.getResponseMessage());
            }
        } catch (IOException e) {
            System.out.println("Error uploading PDF: " + e.getMessage());
        }
    }
}