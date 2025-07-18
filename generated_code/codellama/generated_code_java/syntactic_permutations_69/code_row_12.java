import java.io.*;

public class ImageUploader {
    public static void main(String[] args) throws IOException {
        // Call uploadImage() method
        String filePath = "/path/to/imageFile";
        byte[] imageBytes = readImageFile(filePath);
        uploadImage(imageBytes);
    }

    private static byte[] readImageFile(String filePath) throws IOException {
        // Read the contents of the file into a byte array
        FileInputStream inputStream = new FileInputStream(filePath);
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        byte[] buffer = new byte[4096];

        int bytesRead;
        while ((bytesRead = inputStream.read(buffer)) != -1) {
            outputStream.write(buffer, 0, bytesRead);
        }

        return outputStream.toByteArray();
    }

    private static void uploadImage(byte[] imageBytes) throws IOException {
        // Upload the encoded image to a remote server
        String url = "https://example.com/upload";
        URL obj = new URL(url);

        HttpURLConnection con = (HttpURLConnection) obj.openConnection();
        con.setRequestMethod("POST");

        // Set the necessary headers and content type
        con.setRequestProperty("User-Agent", "Mozilla/5.0");
        con.setRequestProperty("Content-Type", "application/octet-stream");

        OutputStream outputStream = con.getOutputStream();
        outputStream.write(imageBytes);
        outputStream.flush();
        outputStream.close();
    }
}