import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class FileUploader {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.pdf";
        String uploadUrl = "http://localhost:8080/upload"; // Change the port if necessary

        try (FileInputStream fileInputStream = new FileInputStream(filePath)) {
            URL url = new URL(uploadUrl);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");
            connection.setRequestProperty("Connection", "Keep-Alive");
            connection.setRequestProperty("Accept", "text/plain");

            try (OutputStream outputStream = connection.getOutputStream()) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                    outputStream.write(buffer, 0, bytesRead);
                }

                if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    System.out.println("File uploaded successfully.");
                } else {
                    System.err.println("File upload failed: " + connection.getResponseMessage());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Note: Make sure your web server is configured to handle file uploads at the specified endpoint (`/upload`) and that it is running on `localhost` with port `8080`. Adjust the `filePath` variable accordingly to point to your PDF file.