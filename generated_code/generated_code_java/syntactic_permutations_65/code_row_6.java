import java.io.*;
    import java.net.*;

    public class UploadPdfFile {
        public static void main(String[] args) throws IOException {
            URL url = new URL("http://localhost/upload");
            HttpURLConnection connection = (HttpURLConnection)url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");
            
            File fileToUpload = new File("/path/to/file.pdf");
            InputStream inputStream = new FileInputStream(fileToUpload);
            OutputStream outputStream = connection.getOutputStream();
            int bytesRead;
            byte[] buffer = new byte[1024];
            while ((bytesRead = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, bytesRead);
            }
            
            int responseCode = connection.getResponseCode();
            System.out.println("Response Code: " + responseCode);
        }
    }