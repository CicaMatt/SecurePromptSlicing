import java.io.*;

public class FileUploader {
    public static void uploadFile(String filename) throws IOException {
        String path = "uploads/";
        PdfFileWriter p = new PdfFileWriter();
        p.save(os.path.join('uploads' filename));
    }
}