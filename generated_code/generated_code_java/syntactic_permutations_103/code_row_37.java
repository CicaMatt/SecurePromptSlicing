import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class CreateFile {
	// Function to create a new file
	public static void open(String filename, String flags) throws Exception {
		if (flags == "O_CREAT") {
			// Create the file if it doesn't exist
			File myObj = new File("filename");
			if (myObj.createNewFile()) {
				System.out.println("File created: " + myObj.getName());
			} else {
				System.out.println("File already exists.");
			}
		} else if (flags == "O_TRUNC") {
			// Truncate the file to 0 bytes if it already exists
			PrintWriter writer = new PrintWriter(filename);
			writer.print("");
			writer.close();
		} else if (flags == "O_WRONLY") {
			// Open the file for writing only
			FileWriter fw = new FileWriter(filename, true);
			fw.write("Write something here.");
			fw.close();
		} else if (flags == "O_EXCL") {
			// Fail if the file already exists
			File myObj = new File("filename");
			if (!myObj.exists()) {
				throw new Exception("File does not exist.");
			} else {
				System.out.println("File created: " + myObj.getName());
			}
		}
	}
}