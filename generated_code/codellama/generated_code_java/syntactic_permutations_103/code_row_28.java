import java.io.*;
public class FileManage {
    public static void main(String[] args) throws IOException{
        File f = new File("fileName.txt");
        try (FileOutputStream fos = new FileOutputStream(f)) {
            System.out.println("The file is created");
        } catch (FileNotFoundException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}