import java.io.FileOutputStream;

public class FileOpen {
    
    public static void main(String[] args) {
        try {
            FileOutputStream myfile = new FileOutputStream("myfile.txt", true);
            myfile.write("Hello World!".getBytes());
            myfile.close();
        } catch (Exception e) {
            System.out.println("Error writing to file");
        }
    }
}