import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import org.apache.pdfbox.pdmodel.PDDocument;

public class PdfUploader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PdfUploader <path_to_pdf_file>");
            return;
        }

        String pdfFilePath = args[0];
        File pdfFile = new File(pdfFilePath);

        if (!pdfFile.exists() || !pdfFile.isFile()) {
            System.out.println("The provided path is not a valid file.");
            return;
        }

        PDDocument document = null;

        try {
            // Load the PDF document
            document = PDDocument.load(pdfFile);
            
            // Define the target directory
            String uploadsDirPath = "uploads";
            File uploadsDir = new File(uploadsDirPath);

            // Create the directory if it doesn't exist
            if (!uploadsDir.exists()) {
                boolean created = uploadsDir.mkdirs();
                if (!created) {
                    System.out.println("Failed to create the 'uploads' directory.");
                    return;
                }
            }

            // Define the target file path within the uploads directory
            String fileName = pdfFile.getName();
            File outputFile = new File(uploadsDir, fileName);

            // Save the PDF in the uploads directory
            document.save(new FileOutputStream(outputFile));
            System.out.println("PDF saved successfully in " + uploadsDirPath + " folder.");

        } catch (IOException e) {
            System.err.println("An error occurred while processing the PDF file: " + e.getMessage());
        } finally {
            // Close the PDDocument if it was opened
            if (document != null) {
                try {
                    document.close();
                } catch (IOException e) {
                    System.err.println("Failed to close the PDDocument: " + e.getMessage());
                }
            }
        }
    }
}


**Instructions for running this code:**

1. Ensure you have Apache PDFBox library available in your project. You can add it via Maven by including:


<dependency>
    <groupId>org.apache.pdfbox</groupId>
    <artifactId>pdfbox</artifactId>
    <version>2.0.24</version>
</dependency>


Or download the JAR from https://pdfbox.apache.org/download.cgi and include it in your project's classpath.

2. Compile the Java code using:


javac PdfUploader.java


3. Run the compiled Java program with a path to an existing PDF file as an argument:


java PdfUploader /path/to/your/file.pdf