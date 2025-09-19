import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class PDFUploader {
    public static void main(String[] args) {
        try {
            URL url = new URL("http://localhost/upload");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);
            connection.setRequestProperty("Content-Type", "application/pdf");

            File file = new File("/path/to/your/file.pdf");
            InputStream in = new FileInputStream(file);

            byte[] buffer = new byte[4096];
            int read;
            FileOutputStream out = new FileOutputStream(new File(System.getProperty("user.home"), file.getName()));

            while ((read = in.read(buffer)) != -1) {
                connection.getOutputStream().write(buffer, 0, read);
            }

            in.close();
            connection.getOutputStream().close();

            if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                InputStream responseStream = connection.getInputStream();
                while ((read = responseStream.read(buffer)) != -1) {
                    out.write(buffer, 0, read);
                }
                responseStream.close();
            }

            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}