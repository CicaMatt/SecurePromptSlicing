import java.io.*;
public class FileCreator {
    public static void main(String[] args) throws IOException {
        try (FileOutputStream fos = new FileOutputStream("filename", true)){
        } catch (IOException e){
            System.err.println("Error creating file.");
        }
        if (!file.exists()) { file.createNewFile();
        } else {
            throw new IOException("File already exists!");
        }
    }
}