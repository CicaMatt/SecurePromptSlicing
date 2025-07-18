import java.io.*;

public class UploadPDF {
    public static void main(String[] args) throws IOException {
        // Read PDF file from form input
        String pdfContent = "<<< EOF\n" +
            "<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">\n" +
            "  <input type=\"file\" name=\"pdf\">\n" +
            "</form>\n" +
            "EOF";
        
        // Write PDF file to local disk
        File pdfFile = new File("uploads/example.pdf");
        BufferedWriter writer = new BufferedWriter(new FileWriter(pdfFile));
        writer.write(pdfContent);
        writer.close();
    }
}