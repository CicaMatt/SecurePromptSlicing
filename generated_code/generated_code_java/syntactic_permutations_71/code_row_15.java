import java.io.*;

public class FileUpload {
    public static void main(String[] args) throws Exception {
        // Create a temporary file to store the uploaded file
        File tempFile = File.createTempFile("uploaded_file", ".tmp");
        
        // Get the input and output streams of the request and response
        InputStream is = new FileInputStream(tempFile);
        OutputStream os = new FileOutputStream(tempFile);
        
        // Read the uploaded file from the input stream and write it to the output stream
        int read;
        while ((read = is.read()) != -1) {
            os.write(read);
        }
        
        // Close the input and output streams
        is.close();
        os.close();
    }
}