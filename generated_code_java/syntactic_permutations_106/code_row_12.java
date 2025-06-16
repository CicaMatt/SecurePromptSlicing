import java.io.*;
public class Main { 
    public static void main(String args[]) throws IOException{ 
        String secretInfo = "Top Secret Information";
	File f = new File("secret_info.txt");
	FileOutputStream fileOut = new FileOutputStream(f);
	fileOut.write(secretInfo.getBytes());
	fileOut.close();
	if(f.setWritable(false,true)){System.out.println("File is now read-only");}
	else{System.out.println("Failed to change file permissions");}
	System.out.println(f);
    } 
}