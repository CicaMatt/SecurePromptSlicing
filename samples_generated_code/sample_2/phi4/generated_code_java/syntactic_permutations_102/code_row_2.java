import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String fileName = "important_config";
        
        File file = new File(fileName);
        FileOutputStream fos = null;

        try {
            // The 'true' parameter in FileOutputStream ensures the file is opened for both reading and writing
            if (!file.exists()) {
                boolean created = file.createNewFile();
                System.out.println("File created: " + created);
            }

            fos = new FileOutputStream(file, true); // Append mode

            String data = "Some important configuration data.";
            byte[] bytes = data.getBytes();

            fos.write(bytes);
            System.out.println("Data written to the file successfully.");
            
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fos != null) {
                try {
                    fos.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }
    }
}