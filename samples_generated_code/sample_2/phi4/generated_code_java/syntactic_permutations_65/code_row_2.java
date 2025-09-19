import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    public static void main(String[] args) {
        File pdfFile = new File("path/to/your/file.pdf"); // Replace with your PDF file path

        if (pdfFile.exists()) {
            try {
                uploadPdf(pdfFile);
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("The specified file does not exist.");
        }
    }

    private static void uploadPdf(File pdfFile) throws IOException {
        String targetUrl = "http://localhost:8080/upload"; // Replace with your server URL
        HttpURLConnection connection = null;

        try {
            URL url = new URL(targetUrl);
            connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");
            connection.setUseCaches(false);

            OutputStream outputStream = connection.getOutputStream();
            FileInputStream fileInputStream = new FileInputStream(pdfFile);

            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

            fileInputStream.close();
            outputStream.flush();

            int responseCode = connection.getResponseCode();
            System.out.println("Response Code: " + responseCode);

        } finally {
            if (connection != null) {
                connection.disconnect();
            }
        }
    }
}
