import com.itextpdf.text.Document;
import com.itextpdf.text.pdf.PdfWriter;
import java.io.*;
import javax.servlet.http.Part;
 
public class SavePdf {
   public static void savePdf(Part pdfFile) throws IOException{
      Document document = new Document();
      PdfWriter writer = PdfWriter.getInstance(document, 
                        new FileOutputStream("D:/path/to/pdf/location"));
      writer.open();
      document.open();
      InputStream inputStream = pdfFile.getInputStream();
      OutputStream outputStream = writer.getDirectContent().getAsciiStream();
      int read = 0;
      byte[] bytes = new byte[1024];
      while ((read = inputStream.read(bytes)) != -1) {
            outputStream.write(bytes, 0, read);
      }
      writer.close();
      document.close();
   }
}