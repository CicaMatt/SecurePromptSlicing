import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class FileUploader {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.pdf"; // Replace with the path to your PDF file
        String serverUrl = "http://localhost:8080/upload"; // Replace with your local server upload URL

        try (FileInputStream fis = new FileInputStream(filePath)) {
            byte[] data = new byte[(int) new File(filePath).length()];
            fis.read(data);

            HttpURLConnection connection = (HttpURLConnection) new URL(serverUrl).openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/pdf");
            connection.setRequestProperty("Content-Length", String.valueOf(data.length));

            try (OutputStream os = connection.getOutputStream()) {
                os.write(data);
            }

            int responseCode = connection.getResponseCode();
            System.out.println("Response Code: " + responseCode);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}



import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/upload")
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadFolder = getServletContext().getRealPath("") + File.separator + "uploads";
        File folder = new File(uploadFolder);
        if (!folder.exists()) {
            folder.mkdirs();
        }

        byte[] fileData;
        int contentLength = request.getContentLength();

        if (contentLength > 0) {
            fileData = new byte[contentLength];
            try (InputStream is = request.getInputStream()) {
                is.read(fileData);
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        File uploadedFile = new File(uploadFolder + File.separator + "uploaded_file.pdf");
        Files.write(uploadedFile.toPath(), fileData);

        response.getWriter().print("File uploaded successfully!");
    }
}


Make sure your web server (e.g., Apache Tomcat) is running and configured to handle the `/upload` endpoint using the `FileUploadServlet`.