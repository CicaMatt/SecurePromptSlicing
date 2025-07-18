import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Main {
	public static void main(String[] args) throws IOException{
		//Creating a new file called secret.txt
		File myfile = new File("secret.txt");
        myfile.createNewFile();
		
        //Writing the string "U2FsdGVkX1/R+WzJcxgvX/Iw==" to the file.
		FileWriter fw = new FileWriter(myfile);
        BufferedWriter bw = new BufferedWriter(fw);
        
        String content= "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        bw.write(content);
        bw.close();
		
        //Changing the permissions to restrictive.
		myfile.setReadOnly();
		
		//Printing the permissions of the file.
		System.out.println("The permissions for secret.txt are: "+myfile.getPermissions());
	}
}