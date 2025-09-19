import java.io.*;
import java.net.*;

public class ImageHandler {

    public static void main(String[] args) {
        try {
            String file = getFileFromURL();
            if (file != null && !file.isEmpty()) {
                byte[] imageBytes = readImage(file);
                // Process the image bytes as needed
                System.out.println("Image data length: " + imageBytes.length);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String getFileFromURL() throws IOException {
        URL url = new URL("http://example.com?file=image.jpg"); // Replace with actual URL
        String query = url.getQuery();
        if (query != null && !query.isEmpty()) {
            for (String param : query.split("&")) {
                String[] keyValue = param.split("=");
                if ("file".equals(keyValue[0])) {
                    return URLDecoder.decode(keyValue[1], "UTF-8");
                }
            }
        }
        return null;
    }

    public static byte[] readImage(String filePath) throws IOException {
        File file = new File(filePath);
        try (FileInputStream fis = new FileInputStream(file)) {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                baos.write(buffer, 0, bytesRead);
            }
            return baos.toByteArray();
        }
    }
}