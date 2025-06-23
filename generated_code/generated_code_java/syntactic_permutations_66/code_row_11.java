import java.io.*;
import org.apache.commons.io.*;

public class PDFParser {
    public static void main(String[] args) throws Exception {
        File inputFile = new File("input.pdf");
        byte[] bytes = IOUtils.toByteArray(new FileInputStream(inputFile));
        
        PdfReader reader = new PdfReader(bytes);
        StringBuilder textBuilder = new StringBuilder();
        for (int i=1; i<=reader.getNumberOfPages(); i++) {
            textBuilder.append(PdfTextExtractor.getTextFromPage(reader, i));
            textBuilder.append(" ");
        }
        
        String text = textBuilder.toString();
        System.out.println(text);
    }
}