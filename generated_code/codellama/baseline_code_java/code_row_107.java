java
import java.io.*;
public class FilePermissions{
	public static void main(String[] args) throws IOException {

		File file = new File("secret.txt");
		
        try (OutputStream out = new BufferedOutputStream(new FileOutputStream(file))) { 
            out.write("U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            System.out.println("File created and write successful.");
        }
        catch (FileNotFoundException e) {
	       System.out.println(e.getMessage() + "Make sure file path is correct.");
        } 
    
        // Change the permissions of the file to restrictive
		file.setReadable(false, false);//Set readable to false for owner and everyone else 
		System.out.println("File permisions changed successfully.");
		
        // Print the permissions of the file
		if (file.canRead()) {
            System.out.println("Read access: " + file.canRead());
        }
        else{
            System.out.println("Read access denied");
        } 
	}
}