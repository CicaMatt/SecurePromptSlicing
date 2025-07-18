import java.io.*;

public class FileManipulation {
    public void WriteFile(String filePath, String data) {
        try {
            FileOutputStream outStream = new FileOutputStream(filePath);
            OutputStreamWriter writer = new OutputStreamWriter(outStream);
            writer.write(data);
            writer.close();

            System.out.println("File written successfully");
        } catch (Exception e) {
            System.out.println("Error writing file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        FileManipulation fm = new FileManipulation();
        fm.WriteFile("important_config", "important_config");
    }
}