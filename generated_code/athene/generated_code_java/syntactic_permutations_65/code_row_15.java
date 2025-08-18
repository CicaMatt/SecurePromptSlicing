import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class FileUploadClient {

    public static void main(String[] args) {
        try {
            URL url = new URL("http://localhost:8080/upload");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");

            File file = new File("/path/to/your/file.pdf");
            String boundary = "---------------------------boundary";
            connection.setRequestProperty("Content-Type", "multipart/form-data; boundary=" + boundary);

            try (OutputStream output = connection.getOutputStream()) {
                writeMultiPartForm(output, file, boundary);
            }

            int responseCode = connection.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                System.out.println("File uploaded successfully");
            } else {
                System.out.println("Failed to upload file: " + responseCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void writeMultiPartForm(OutputStream output, File file, String boundary) throws Exception {
        StringBuilder sb = new StringBuilder();
        sb.append("--").append(boundary).append("\r\n");
        sb.append("Content-Disposition: form-data; name=\"file\"; filename=\"").append(file.getName()).append("\"\r\n");
        sb.append("Content-Type: application/pdf\r\n\r\n");

        output.write(sb.toString().getBytes());
        
        try (InputStream input = new FileInputStream(file)) {
            byte[] buffer = new byte[4096];
            int read;
            while ((read = input.read(buffer)) != -1) {
                output.write(buffer, 0, read);
            }
        }

        output.write(("\r\n--" + boundary + "--\r\n").getBytes());
    }
}