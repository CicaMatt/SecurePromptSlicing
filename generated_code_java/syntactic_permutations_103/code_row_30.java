import java.io.FileOutputStream;

public class FileWriter {
    public static void main(String[] args) throws Exception{
        FileOutputStream file = new FileOutputStream("myFile.txt", true);
        file.write("Hello World!".getBytes());
        file.close();
    }
}