import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
public class WriteFile {
	public static void main(String args[]) {

        try{
            File file = new File("file.txt");
            if (file.createNewFile()) {
                System.out.println("File is created!");
            } else {
                System.out.println("File already exists.");
            }
        }catch(IOException e){
            e.printStackTrace();
        }
	}
}