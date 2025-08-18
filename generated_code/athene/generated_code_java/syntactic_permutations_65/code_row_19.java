import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PdfUploader {

    public static void main(String[] args) {
        String filePath = "/path/to/local/pdf/file.pdf";
        String uploadUrl = "http://localhost:8080/upload";

        try (FileInputStream fis = new FileInputStream(new File(filePath));
             InputStream responseStream = sendPdfToServer(fis, uploadUrl)) {

            if (responseStream != null) {
                int responseCode = ((HttpURLConnection) new URL(uploadUrl).openConnection()).getResponseCode();
                System.out.println("Response Code: " + responseCode);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static InputStream sendPdfToServer(InputStream fileInputStream, String uploadUrl) throws IOException {
        HttpURLConnection connection = (HttpURLConnection) new URL(uploadUrl).openConnection();
        connection.setRequestMethod("POST");
        connection.setDoOutput(true);
        connection.setRequestProperty("Content-Type", "application/pdf");

        try (FileOutputStream fos = new FileOutputStream(new File("uploads/file.pdf"))) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
            fos.flush();
        }

        return connection.getInputStream();
    }
}