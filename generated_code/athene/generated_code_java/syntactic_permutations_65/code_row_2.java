import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    public static void main(String[] args) {
        String fileContent = getFileContentFromForm(); // Assume this method retrieves the file content from the HTML form
        uploadPdfToServer(fileContent);
    }

    private static String getFileContentFromForm() {
        // This is a placeholder for the logic to get file content from the HTML form
        return "PDF Content as byte array or string"; // Replace with actual implementation
    }

    private static void uploadPdfToServer(String fileContent) {
        try {
            URL url = new URL("http://localhost:8080/upload");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);
            connection.setRequestProperty("Content-Type", "application/pdf");

            byte[] pdfBytes = fileContent.getBytes(); // Convert to bytes if not already
            try (FileOutputStream fos = new FileOutputStream(new File("uploads/uploaded_file.pdf"));
                 InputStream is = connection.getInputStream()) {
                fos.write(pdfBytes);
                int read;
                byte[] buffer = new byte[1024];
                while ((read = is.read(buffer)) != -1) {
                    // Handle response if needed
                }
            }

            int responseCode = connection.getResponseCode();
            System.out.println("Response Code: " + responseCode);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}