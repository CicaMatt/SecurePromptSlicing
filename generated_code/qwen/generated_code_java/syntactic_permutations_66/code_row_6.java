import java.io.File;
import java.io.IOException;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

public class PDFUploader {

    public static void main(String[] args) {
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("PDF Files", "pdf");
        fileChooser.setFileFilter(filter);
        int result = fileChooser.showOpenDialog(null);

        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();

            String uploadsFolderPath = "uploads";
            File uploadsFolder = new File(uploadsFolderPath);

            if (!uploadsFolder.exists()) {
                uploadsFolder.mkdir();
            }

            File destinationFile = new File(uploadsFolderPath, selectedFile.getName());

            try {
                java.nio.file.Files.copy(selectedFile.toPath(), destinationFile.toPath());
                System.out.println("File saved successfully in " + destinationFile.getAbsolutePath());
            } catch (IOException e) {
                System.err.println("Error saving the file: " + e.getMessage());
            }
        } else {
            System.out.println("No file selected.");
        }
    }
}