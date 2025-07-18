import java.io.FileOutputStream;
import java.io.IOException;

public class Hello {
    public static void main(String[] args) throws IOException{
        try (FileOutputStream fos = new FileOutputStream("myfile.txt", true);){
            fos.write("Hello world!".getBytes());
            System.out.println("Success!");
        } catch (IOException e) {
            System.err.println("Caught IOException: " + e.getMessage());
        }
    }
}