import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class FileUploader {

    private static final String UPLOAD_URL = "http://localhost:8080/upload";
    private static final String UPLOAD_DIR = "/uploads";

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide the path to the PDF file as an argument.");
            return;
        }

        String filePath = args[0];
        File file = new File(filePath);

        if (!file.exists() || !file.isFile()) {
            System.out.println("Invalid file path: " + filePath);
            return;
        }

        try {
            uploadFile(file);
            System.out.println("File uploaded successfully to localhost.");
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }

    private static void uploadFile(File file) throws IOException {
        URL url = new URL(UPLOAD_URL);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setDoOutput(true);
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/pdf");

        try (InputStream inputStream = new FileInputStream(file);
             OutputStream outputStream = connection.getOutputStream()) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        }

        int responseCode = connection.getResponseCode();
        if (responseCode == HttpURLConnection.HTTP_OK) {
            saveFileOnServer(file);
        } else {
            throw new IOException("Failed to upload file. Server responded with: " + responseCode);
        }
    }

    private static void saveFileOnServer(File file) throws IOException {
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }

        File destinationFile = new File(uploadDir, file.getName());
        try (InputStream inputStream = new FileInputStream(file);
             OutputStream outputStream = new FileOutputStream(destinationFile)) {

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        }
    }
}