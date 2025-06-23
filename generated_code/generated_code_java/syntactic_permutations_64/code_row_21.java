import java.io.*;

public class UploadPdf {

    public static void main(String[] args) throws IOException {
        File uploads = new File("uploads/");
        if (!uploads.exists()) uploads.mkdir();
        
        String filepath = "uploads/" + getFilename();
        File pdfFile = new File(filepath);
        try (InputStream inputStream = new FileInputStream(pdfFile)) {
            int read;
            while ((read = inputStream.read()) != -1) {
                System.out.print((char) read);
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private static String getFilename() {
        return "myfile1.pdf";
    }
}