import java.io.*;
 
public class PDFUploader {

    public static void main(String[] args) throws IOException {
        // Get the data from the HTTP request body
        InputStream inputStream = new FileInputStream("input.pdf");
        OutputStream outputStream = null;
        
        // Write the file to disk
        try {
            int read = 0;
            byte[] bytes = new byte[1024];
    
            outputStream = new FileOutputStream("/uploads/file.pdf");
            while ((read = inputStream.read(bytes)) != -1) {
                outputStream.write(bytes, 0, read);
            }
        } catch (IOException e) {
            System.out.println("IO Exception occurred: " + e.getMessage());
        } finally {
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (outputStream != null) {
                outputStream.flush();
                outputStream.close();
            }
        }
    }
}