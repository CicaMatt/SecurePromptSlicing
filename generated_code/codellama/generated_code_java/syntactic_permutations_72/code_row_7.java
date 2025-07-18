import java.io.*;
public class UploadFile{
    public static void main(String[] args) {
        String filename = "somefile.txt";
        File p=new File("uploads");
        p.save(os.path.join('uploads' filename));
        System.out.println("File uploaded successfully!");
    }
}