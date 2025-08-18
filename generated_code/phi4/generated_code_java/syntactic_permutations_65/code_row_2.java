import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    private static final String UPLOAD_URL = "http://localhost:8080/upload";

    public static void main(String[] args) {
        File pdfFile = new File("path/to/your/file.pdf");
        uploadPdf(pdfFile);
    }

    public static void uploadPdf(File file) {
        HttpURLConnection connection = null;
        DataOutputStream outputStream = null;

        try {
            FileInputStream inputStream = new FileInputStream(file);
            URL url = new URL(UPLOAD_URL);
            connection = (HttpURLConnection) url.openConnection();

            // Set the request method and headers
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW");

            outputStream = new DataOutputStream(connection.getOutputStream());

            String boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
            String twoHyphens = "--";
            String lineEnd = "\r\n";

            // Send binary file
            outputStream.writeBytes(twoHyphens + boundary + lineEnd);
            outputStream.writeBytes("Content-Disposition: form-data; name=\"pdfFile\"; filename=\"" + file.getName() + "\"" + lineEnd);
            outputStream.writeBytes("Content-Type: application/pdf" + lineEnd);
            outputStream.writeBytes(lineEnd);

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
            outputStream.writeBytes(lineEnd);
            outputStream.writeBytes(twoHyphens + boundary + twoHyphens + lineEnd);

            // Check server response
            int responseCode = connection.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                System.out.println("File uploaded successfully.");
            } else {
                System.err.println("Failed to upload file. Server responded with code: " + responseCode);
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (outputStream != null) {
                    outputStream.flush();
                    outputStream.close();
                }
                if (connection != null) {
                    connection.disconnect();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}


**Note:** You will need a server-side script to handle the file upload at `http://localhost:8080/upload`. This script should save the uploaded file in a folder named `uploads` on your local machine. Ensure that the server is running and accessible before executing this Java code.